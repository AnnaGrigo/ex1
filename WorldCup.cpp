#include "WorldCup.h"

WorldCup::WorldCup() {
    top_player_score = 0;
    top_player = nullptr;
    legal_teams_by_id = AvlTree<int, Team*>();
    teams_by_id = AvlTree<int, Team*>();
    all_players_by_id = AvlTree<int, Player*>();
    all_players_by_score = AvlTree<Score, Player*>();
}

WorldCup::~WorldCup() {

}

StatusType WorldCup::AddTeam(int teamID, int points) {
    /*
    if (teamID <= 0 || points < 0) {
        return StatusType::INVALID_INPUT;
    }
    if (teams_by_id.Find(teamID) != teams_by_id.end()) {
        return StatusType::FAILURE;
    }
    Team* new_team = new Team();
    if (new_team == nullptr) {
        return StatusType::ALLOCATION_ERROR;
    }
    new_team->team_id = teamID;
    new_team->points = points;
    new_team->value = 0;
    new_team->num_of_goalkeepers = 0;
    new_team->top_team_player_score = 0;
    new_team->top_team_player = nullptr;
    new_team->team_players_by_id = AvlTree<int, Player*>();
    new_team->team_players_by_score = AvlTree<Score, Player*>();
    teams_by_id.Insert({teamID, new_team});
    legal_teams_by_id.Insert({teamID, new_team});
    return StatusType::SUCCESS;
     */
}

StatusType WorldCup::RemoveTeam(int teamID) {
    return StatusType::FAILURE;
}

StatusType WorldCup::AddPlayer(int playerID, int teamID, int GamesPlayed, int goals, int tickets, bool isGoalkeeper) {
    return StatusType::FAILURE;
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




