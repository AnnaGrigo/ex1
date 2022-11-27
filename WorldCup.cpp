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

}




