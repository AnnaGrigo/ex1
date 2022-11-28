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
    if ((teams_by_id.Find(teamID))->key != teamID) {
        return StatusType::FAILURE;
    }
    Team* new_team = new Team(teamID, points);
    if (!new_team) {
        return StatusType::ALLOCATION_ERROR;
    }
    return teams_by_id.Insert(teamID, new_team);
}

StatusType WorldCup::RemoveTeam(int teamID) {
    return StatusType::FAILURE;
}

StatusType WorldCup::AddPlayer(int playerID, int teamID, int GamesPlayed, int goals, int cards, bool isGoalkeeper) {
    if ((all_players_by_id.Find(playerID))->key != playerID) {
        return StatusType::FAILURE;
    }
    if ((teams_by_id.Find(teamID))->key != teamID) {
        return StatusType::FAILURE;
    }
    Player* new_player = new Player(playerID, teamID,
                                    GamesPlayed, goals, cards, isGoalkeeper);
    if (!new_player) {
        return StatusType::ALLOCATION_ERROR;
    }
    Score new_player_score = Score(goals, cards, playerID);
    if (new_player_score > top_player_score) {
        top_player_score = new_player_score;
        top_player = new_player;
    }
    StatusType status = all_players_by_id.Insert(playerID, new_player);
    if (status != StatusType::SUCCESS) {
        return status;
    }
    //status = all_players_by_score.Insert(new_player_score, new_player);
    if (status != StatusType::SUCCESS) {
        return status;
    }


}

StatusType WorldCup::RemovePlayer(int playerID) {
    return StatusType::FAILURE;
}

StatusType WorldCup::UpdatePlayer(int playerID, int gamesPlayed, int ScoredGoals, int CardsReceived) {
    return StatusType::FAILURE;
}

StatusType WorldCup::PlayMatch(int teamID1, int teamID2) {
    return StatusType::FAILURE;
}

output_t<int> WorldCup::GetNumPlayedGames(int playerID) {
    return nullptr;
}

output_t<int> WorldCup::GetTeamPoints(int teamID) {
    return nullptr;
}

StatusType WorldCup::UniteTeams(int teamID1, int teamID2, int NewTeamId) {
    return StatusType::FAILURE;
}

output_t<int> WorldCup::GetTopScorer(int teamID) {
    return nullptr;
}

output_t<int> WorldCup::GetAllPlayersCount(int teamID) {
    return nullptr;
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




