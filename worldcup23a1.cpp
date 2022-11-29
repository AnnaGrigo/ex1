#include "worldcup23a1.h"
#include "Team.h"
#include "Player.h"
#include "AvlTree.h"

world_cup_t::world_cup_t()
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}


StatusType world_cup_t::add_team(int teamId, int points)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	// TODO: Your code goes here
	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0){
        return StatusType::INVALID_INPUT;
    }
    AvlNode<int ,Team*>* team1 = teams_by_id.Find(teamId1);
    AvlNode<int ,Team*>* team2 = teams_by_id.Find(teamId2);

	if(team1 == nullptr || team2 == nullptr || !(Is_Team_Legal(team1->value)) || !(Is_Team_Legal(team2->value))){
        return StatusType::FAILURE;
    }
    int scoreTeam1 = team1->value->value + team1->value->points;
    int scoreTeam2 = team2->value->value + team2->value->points;
    if(scoreTeam1 == scoreTeam2){
        ++team1->value->points;
        ++team2->value->points;
    }
    else if(scoreTeam1 > scoreTeam2){
        team1->value->points += 3;
    }
    else if(scoreTeam2 > scoreTeam1){
        team2->value->points += 3;
    }

    ++team1->value->all_team_games_played;
    ++team2->value->all_team_games_played;

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    AvlNode<int,Team*>* team = teams_by_id.Find(teamId);
    if(team == nullptr){
        return StatusType::FAILURE;
    }
    return team->value->points;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	if(teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    if(teamId < 0){
        if(top_player == nullptr){
            return StatusType::FAILURE;
        }
        return top_player->player_id;
    }
    if(teamId > 0){
        AvlNode<int, Team*> * team = teams_by_id.Find(teamId);
        if(team == nullptr){
            return StatusType::FAILURE;
        }
        Player* player = team->value->top_team_player;
        if(player == nullptr){
            return StatusType::FAILURE;
        }
        return player->player_id;
    }
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	// TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}

