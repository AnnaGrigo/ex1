
#include "Team.h"

Team::Team(int team_id, int points) {
    this->team_id = team_id;
    this->points = points;
    this->value = points;
    this->num_of_goalkeepers = 0;
    this->top_team_player_score = Score();
    this->top_team_player = nullptr;
    this->team_players_by_id = AvlTree<int, Player*>();
    this->team_players_by_score = AvlTree<Score, Player*>();
}
