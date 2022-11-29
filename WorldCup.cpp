#include "WorldCup.h"

WorldCup::WorldCup() {
    top_player_score = Score();
    top_player = nullptr;
    legal_teams_by_id = AvlTree<int, Team*>();
    teams_by_id = AvlTree<int, Team*>();
    all_players_by_id = AvlTree<int, Player*>();
    all_players_by_score = AvlTree<Score, Player*>();
}

WorldCup::~WorldCup() {

}

StatusType WorldCup::AddTeam(int teamID, int points) {
    //check if team already exists
    if (teams_by_id.Find(teamID) != nullptr) {
        return StatusType::FAILURE;
    }
    Team* new_team = new Team(teamID, points);
    if (!new_team) {
        return StatusType::ALLOCATION_ERROR;
    }
    return teams_by_id.Insert(teamID, new_team);
}

StatusType WorldCup::RemoveTeam(int teamID) {
    //check if team exists
    if ((teams_by_id.Find(teamID))->key != teamID) {
        return StatusType::FAILURE;
    }
    Team *my_team = teams_by_id.Find(teamID)->value;
    //check if team is empty
    if(my_team->team_players_by_id.size > 0) {
        return StatusType::FAILURE;
    }
    StatusType stats = teams_by_id.Delete(teamID);
}

StatusType WorldCup::AddPlayer(int playerID, int teamID, int GamesPlayed, int goals, int cards, bool isGoalkeeper) {
    //check if team/player already exists
    if (all_players_by_id.Find(playerID) != nullptr) {
        return StatusType::FAILURE;
    }
    if (teams_by_id.Find(teamID) != nullptr) {
        return StatusType::FAILURE;
    }
    Player* new_player = new Player(playerID, teamID,
                                    GamesPlayed, goals, cards, isGoalkeeper);
    if (!new_player) {
        return StatusType::ALLOCATION_ERROR;
    }
    Team* my_team = (teams_by_id.Find(teamID))->value;
    new_player->my_team = my_team;
    //update team goalkeepers
    if(new_player->is_goalkeeper) {
        my_team->num_of_goalkeepers++;
    }
    //update team value
    my_team->value += (new_player->goals - new_player->cards);
    //check if new player is the new top player
    Score new_player_score = Score(goals, cards, playerID);
    if (new_player_score > top_player_score) {
        top_player_score = new_player_score;
        top_player = new_player;
    }
    if (new_player_score > my_team->top_team_player_score) {
        my_team->top_team_player_score = new_player_score;
        my_team->top_team_player = new_player;
    }
    //insert player to all players by id tree
    StatusType status = all_players_by_id.Insert(playerID, new_player);
    if (status != StatusType::SUCCESS) {
        return status;
    }
    //insert player to all players by score tree
    Score new_player_score_all = Score(goals, cards, playerID);
    status = all_players_by_score.Insert(new_player_score_all, new_player);
    if (status != StatusType::SUCCESS) {
        return status;
    }
    //insert player to team players by id tree
    status = my_team->team_players_by_id.Insert(playerID, new_player);
    if (status != StatusType::SUCCESS) {
        return status;
    }
    //insert player to team players by score tree
    Score new_player_score_team = Score(goals, cards, playerID);
    status = my_team->team_players_by_score.Insert(new_player_score_team, new_player);
    if (status != StatusType::SUCCESS) {
        return status;
    }
    //check if to insert team to legal teams by id tree
    if(Is_Team_Legal(my_team))
    {
        status = legal_teams_by_id.Insert(teamID, my_team);
        if(status != StatusType::SUCCESS) {
            return status;
        }
    }
    return StatusType::SUCCESS;

}

StatusType WorldCup::RemovePlayer(int playerID) {
    if(all_players_by_id.Find(playerID) == nullptr) {
        return StatusType::FAILURE;
    }
    Player* player_to_remove = (all_players_by_id.Find(playerID))->value;
    Team* my_team = player_to_remove->my_team;
    bool was_team_legal = Is_Team_Legal(my_team);
    //update team goalkeepers
    if(player_to_remove->is_goalkeeper) {
        my_team->num_of_goalkeepers--;
    }
    //update team value
    my_team->value -= (player_to_remove->goals - player_to_remove->cards);
    //remove player from all players by id tree
    StatusType status = all_players_by_id.Delete(playerID);
    if(status != StatusType::SUCCESS) {
        return status;
    }
    //remove player from all players by score tree
    Score player_score_all = Score(player_to_remove->goals, player_to_remove->cards, playerID);
    status = all_players_by_score.Delete(player_score_all);
    if(status != StatusType::SUCCESS) {
        return status;
    }
    //remove player from team players by id tree
    status = my_team->team_players_by_id.Delete(playerID);
    if(status != StatusType::SUCCESS) {
        return status;
    }
    //remove player from team players by score tree
    Score player_score_team = Score(player_to_remove->goals, player_to_remove->cards, playerID);
    status = my_team->team_players_by_score.Delete(player_score_team);
    if(status != StatusType::SUCCESS) {
        return status;
    }
    //check if to remove team from legal teams by id tree
    if(!Is_Team_Legal(my_team) && was_team_legal)
    {
        status = legal_teams_by_id.Delete(my_team->team_id);
        if(status != StatusType::SUCCESS) {
            return status;
        }
    }
    //check if to update top player
    if(player_to_remove == top_player) {
        if(all_players_by_score.size == 0) {
            top_player = nullptr;
            top_player_score = Score(0, 0, 0);
        }
        else {
            top_player = (findMaxNode(all_players_by_score.root))->value;
            top_player_score = Score(top_player->goals, top_player->cards, top_player->player_id);
        }
    }
    //check if to update top team player
    if(player_to_remove == my_team->top_team_player) {
        if(my_team->team_players_by_score.size == 0) {
            my_team->top_team_player = nullptr;
            my_team->top_team_player_score = Score();
        }
        else {
            my_team->top_team_player = (findMaxNode(my_team->team_players_by_score.root))->value;
            my_team->top_team_player_score =
                    Score(my_team->top_team_player->goals, my_team->top_team_player->cards, my_team->top_team_player->player_id);
        }
    }
    delete player_to_remove;
    return StatusType::SUCCESS;
}

StatusType WorldCup::UpdatePlayer(int playerID, int gamesPlayed, int ScoredGoals, int CardsReceived) {
    Player* my_player = (all_players_by_id.Find(playerID)->value);
    if (my_player->player_id != playerID) {
        return StatusType::FAILURE;
    }
    bool is_goalkeeper = my_player->is_goalkeeper;
    int team_id = my_player->team_id;
    int updated_goals = ScoredGoals + my_player->goals;
    int updated_cards = CardsReceived + my_player->cards;
    int updated_games = gamesPlayed + my_player->own_games_played;
    StatusType status = RemovePlayer(playerID);
    if(status != StatusType::SUCCESS) {
        return status;
    }
    status = AddPlayer(playerID, team_id, updated_games
              , updated_goals , updated_cards, is_goalkeeper);
    return status;
}

StatusType WorldCup::PlayMatch(int teamID1, int teamID2) {
    return StatusType::FAILURE;
}

output_t<int> WorldCup::GetNumPlayedGames(int playerID) {
    if(all_players_by_id.Find(playerID) == nullptr) {
        return StatusType::FAILURE;
    }
    Player* my_player = (all_players_by_id.Find(playerID))->value;
    Team* my_team = my_player->my_team;
    return my_player->own_games_played + my_team->all_team_games_played - my_player->games_team_played;
}

output_t<int> WorldCup::GetTeamPoints(int teamID) {
    return nullptr;
}

StatusType WorldCup::UniteTeams(int teamID1, int teamID2, int NewTeamId) {
    //check if teamID1 and teamID2 exists
    if(teams_by_id.Find(teamID1) == nullptr) {
        return StatusType::FAILURE;
    }
    if(teams_by_id.Find(teamID2) == nullptr) {
        return StatusType::FAILURE;
    }
    //check if NewTeamId exists and its teamID1 or teamID2
    if(teams_by_id.Find(NewTeamId) != nullptr & NewTeamId != teamID1 & NewTeamId != teamID2) {
        return StatusType::FAILURE;
    }



}

output_t<int> WorldCup::GetTopScorer(int teamID) {
    return nullptr;
}

output_t<int> WorldCup::GetAllPlayersCount(int teamID) {
    if(teams_by_id.Find(teamID) == nullptr) {
        return StatusType::FAILURE;
    }
    if(teamID < 0)
    {
        return all_players_by_id.size;
    }
    if(teamID > 0) {
        return (teams_by_id.Find(teamID))->value->team_players_by_id.size;
    }
}

StatusType WorldCup::GetAllPlayers(int teamID, int *const output) {
    return StatusType::FAILURE;
}

output_t<int> WorldCup::GetClosestPlayer(int playerID, int teamID) {
    return nullptr;
}

output_t<int> WorldCup::KnockoutWinner(int MinTeamID, int MaxTeamID) {
    return nullptr;
}




