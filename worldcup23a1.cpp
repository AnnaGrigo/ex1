#include "worldcup23a1.h"
#include "Team.h"
#include "Player.h"
#include "AvlTree.h"

world_cup_t::world_cup_t()
{
    top_player_score = Score();
    top_player = nullptr;
    legal_teams_by_id = AvlTree<int, Team*>();
    teams_by_id = AvlTree<int, Team*>();
    all_players_by_id = AvlTree<int, Player*>();
    all_players_by_score = AvlTree<Score, Player*>();
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}


StatusType world_cup_t::add_team(int teamId, int points)
{
    if(teamId<=0 || points<0){
        return StatusType::INVALID_INPUT;
    }
    //check if team already exists
    if (teams_by_id.Find(teamId) != nullptr) {
        return StatusType::FAILURE;
    }
    Team* new_team = new Team(teamId, points);
    if (!new_team) {
        return StatusType::ALLOCATION_ERROR;
    }
    return teams_by_id.Insert(teamId, new_team);
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId<=0){
        return StatusType::INVALID_INPUT;
    }
    //check if team exists
    if ((teams_by_id.Find(teamId))->key != teamId) {
        return StatusType::FAILURE;
    }
    Team *my_team = teams_by_id.Find(teamId)->value;
    //check if team is empty
    if(my_team->team_players_by_id.size > 0) {
        return StatusType::FAILURE;
    }
    return teams_by_id.Delete(teamId);
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    if(goals < 0 || gamesPlayed < 0 || teamId <= 0 || playerId <= 0 || cards < 0 || (gamesPlayed == 0 && (goals > 0 || cards>0))){
        return StatusType::INVALID_INPUT;
    }
    //check if team/player already exists
    if (all_players_by_id.Find(playerId) != nullptr) {
        return StatusType::FAILURE;
    }
    if (teams_by_id.Find(teamId) == nullptr) {
        return StatusType::FAILURE;
    }
    Player* new_player;
    try{
        new_player = new Player(playerId, teamId,
                                        gamesPlayed, goals, cards, goalKeeper);
    }
    catch (std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }

    Team* my_team = (teams_by_id.Find(teamId))->value;
    new_player->my_team = my_team;
    //update team goalkeepers
    if(new_player->is_goalkeeper) {
        my_team->num_of_goalkeepers++;
    }
    //update team value
    my_team->value += (new_player->goals - new_player->cards);
    //check if new player is the new top player
    Score new_player_score = Score(goals, cards, playerId);
    if (new_player_score > top_player_score) {
        top_player_score = new_player_score;
        top_player = new_player;
    }
    if (new_player_score > my_team->top_team_player_score) {
        my_team->top_team_player_score = new_player_score;
        my_team->top_team_player = new_player;
    }
    //insert player to all players by id tree
    StatusType status = all_players_by_id.Insert(playerId, new_player);
    if (status != StatusType::SUCCESS) {
        return status;
    }
    //insert player to all players by score tree
    Score new_player_score_all = Score(goals, cards, playerId);
    status = all_players_by_score.Insert(new_player_score_all, new_player);
    if (status != StatusType::SUCCESS) {
        return status;
    }
    //insert player to team players by id tree
    status = my_team->team_players_by_id.Insert(playerId, new_player);
    if (status != StatusType::SUCCESS) {
        return status;
    }
    //insert player to team players by score tree
    Score new_player_score_team = Score(goals, cards, playerId);
    status = my_team->team_players_by_score.Insert(new_player_score_team, new_player);
    if (status != StatusType::SUCCESS) {
        return status;
    }
    //check if to insert team to legal teams by id tree
    if(Is_Team_Legal(my_team))
    {
        status = legal_teams_by_id.Insert(teamId, my_team);
        if(status != StatusType::SUCCESS) {
            return status;
        }
    }
    AvlNode<Score, Player*> *x = all_players_by_score.Find(new_player_score_all); //idk why its happening
    //add to new player the closest players InOrder
    new_player->next_player_in_score =
            all_players_by_score.Next_InOrder(all_players_by_score.Find(new_player_score_all))->value;
    new_player->prev_player_in_score =
            all_players_by_score.Prev_InOrder(all_players_by_score.Find(new_player_score_all))->value;
    new_player->next_player_in_score->prev_player_in_score = new_player;
    new_player->prev_player_in_score->next_player_in_score = new_player;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
    if(playerId<=0) {
        return StatusType::INVALID_INPUT;
    }
    if(all_players_by_id.Find(playerId) == nullptr) {
        return StatusType::FAILURE;
    }
    Player* player_to_remove = (all_players_by_id.Find(playerId))->value;
    Team* my_team = player_to_remove->my_team;
    bool was_team_legal = Is_Team_Legal(my_team);
    //update team goalkeepers
    if(player_to_remove->is_goalkeeper) {
        my_team->num_of_goalkeepers--;
    }
    //save the closest players InOrder before removing
    Player* next_player_in_score = player_to_remove->next_player_in_score;
    Player* prev_player_in_score = player_to_remove->prev_player_in_score;
    //update team value
    my_team->value -= (player_to_remove->goals - player_to_remove->cards);
    //remove player from all players by id tree
    StatusType status = all_players_by_id.Delete(playerId);
    if(status != StatusType::SUCCESS) {
        return status;
    }
    //remove player from all players by score tree
    Score player_score_all = Score(player_to_remove->goals, player_to_remove->cards, playerId);
    status = all_players_by_score.Delete(player_score_all);
    if(status != StatusType::SUCCESS) {
        return status;
    }
    //remove player from team players by id tree
    status = my_team->team_players_by_id.Delete(playerId);
    if(status != StatusType::SUCCESS) {
        return status;
    }
    //remove player from team players by score tree
    Score player_score_team = Score(player_to_remove->goals, player_to_remove->cards, playerId);
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
                    Score(my_team->top_team_player->goals,
                          my_team->top_team_player->cards,
                          my_team->top_team_player->player_id);
        }
    }
    //update the closest players InOrder
    next_player_in_score->prev_player_in_score = prev_player_in_score;
    prev_player_in_score->next_player_in_score = next_player_in_score;
    delete player_to_remove;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
    if(playerId<=0 || gamesPlayed<0 || scoredGoals<0 || cardsReceived<0) {
        return StatusType::INVALID_INPUT;
    }
    Player* my_player = (all_players_by_id.Find(playerId)->value);
    if (my_player->player_id != playerId) {
        return StatusType::FAILURE;
    }
    bool is_goalkeeper = my_player->is_goalkeeper;
    int team_id = my_player->team_id;
    int updated_goals = scoredGoals + my_player->goals;
    int updated_cards = cardsReceived + my_player->cards;
    int updated_games = gamesPlayed + my_player->own_games_played;
    StatusType status = remove_player(playerId);
    if(status != StatusType::SUCCESS) {
        return status;
    }
    return add_player(playerId, team_id, updated_games
            , updated_goals , updated_cards, is_goalkeeper);
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
    if(playerId <= 0 ){
        return StatusType::INVALID_INPUT;
    }
    if(all_players_by_id.Find(playerId) == nullptr) {
        return StatusType::FAILURE;
    }
    Player* my_player = (all_players_by_id.Find(playerId))->value;
    Team* my_team = my_player->my_team;
    return my_player->own_games_played + my_team->all_team_games_played - my_player->games_team_played;
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
	if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2 || newTeamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    //check if teamID1 and teamID2 exists
    if(teams_by_id.Find(teamId1) == nullptr) {
        return StatusType::FAILURE;
    }
    if(teams_by_id.Find(teamId2) == nullptr) {
        return StatusType::FAILURE;
    }
    //check if NewTeamId exists and its teamID1 or teamID2
    if(teams_by_id.Find(newTeamId) != nullptr & newTeamId != teamId1 & newTeamId != teamId2) {
        return StatusType::FAILURE;
    }
    Team* team1 = teams_by_id.Find(teamId1)->value;
    Team* team2 = teams_by_id.Find(teamId2)->value;
    change_players_games(team1->team_players_by_id.root,team1->all_team_games_played);
    change_players_games(team2->team_players_by_id.root,team2->all_team_games_played);
    if(team1->team_players_by_id.Merge(team2->team_players_by_id) == StatusType::ALLOCATION_ERROR){
        team1->all_team_games_played = 0;
        team2->all_team_games_played = 0;
        return StatusType::ALLOCATION_ERROR;
    }
    if(team1->team_players_by_score.Merge(team2->team_players_by_score) == StatusType::ALLOCATION_ERROR){
        team1->all_team_games_played = 0;
        team2->all_team_games_played = 0;
        return StatusType::ALLOCATION_ERROR;
    }
    team1->num_of_goalkeepers += team2->num_of_goalkeepers;
    team1->points += team2->points;
    team1->value += team2->value;
    team1->all_team_games_played = 0;
    if(team1->top_team_player_score < team2->top_team_player_score) {
        team1->top_team_player = team2->top_team_player;
        team1->top_team_player_score = team2->top_team_player_score;
    }
    teams_by_id.Delete(teamId1);
    teams_by_id.Delete(teamId2);
    team1->team_id = newTeamId;
    if(teams_by_id.Insert(newTeamId,team1) == StatusType::ALLOCATION_ERROR){
        return StatusType::ALLOCATION_ERROR;
    }
    legal_teams_by_id.Delete(teamId1);
    legal_teams_by_id.Delete(teamId2);
    if(Is_Team_Legal(team1)){
        legal_teams_by_id.Insert(team1->value,team1);
    }
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
    if(teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    if(teams_by_id.Find(teamId) == nullptr) {
        return StatusType::FAILURE;
    }
    if(teamId < 0)
    {
        return all_players_by_id.size;
    }
    if(teamId > 0) {
        return (teams_by_id.Find(teamId))->value->team_players_by_id.size;
    }
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	if(teamId == 0 || output == nullptr){
        return StatusType::INVALID_INPUT;
    }
    int arraySize = 0;
    Pair<Score, Player*>* playerArray;
    if (teamId < 0){
        arraySize = all_players_by_score.size;
        try {
            playerArray = new Pair<Score, Player*>[arraySize];
        }
        catch (std::bad_alloc&){
            return StatusType::ALLOCATION_ERROR;
        }
        playerArray = all_players_by_score.InOrder(all_players_by_score.root , playerArray);
    }
    if (teamId > 0){
        AvlNode<int, Team*>* team = teams_by_id.Find(teamId);
        arraySize = team->value->team_players_by_id.size;
        try {
            playerArray = new Pair<Score, Player*>[arraySize];
        }
        catch (std::bad_alloc&){
            return StatusType::ALLOCATION_ERROR;
        }
        playerArray = team->value->team_players_by_score.InOrder(all_players_by_score.root , playerArray);
    }
    for (int i = 0; i < arraySize; ++i) {
        output[i] = playerArray[i].value->goals;
    }
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	if(playerId <= 0 || teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if(teams_by_id.Find(teamId) == nullptr) {
        return StatusType::FAILURE;
    }
    Team *my_team = teams_by_id.Find(teamId)->value;
    if(my_team->team_players_by_id.Find(playerId) == nullptr) {
        return StatusType::FAILURE;
    }
    if(all_players_by_id.size == 1) {
        return StatusType::FAILURE;
    }
    Player *my_player = my_team->team_players_by_id.Find(playerId)->value;
    int closest_player_id = my_player->Get_Closest_Player
            (my_player->next_player_in_score,my_player->prev_player_in_score);
    return closest_player_id;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	if( minTeamId < 0 || maxTeamId < 0 ||  maxTeamId < minTeamId){
        return StatusType::INVALID_INPUT;
    }
	return 2;
}

