
#ifndef RATUV1_TEAM_H
#define RATUV1_TEAM_H

#include "AvlTree.h"
#include "Player.h"
#include "Score.h"

class Team
{
public:
    int team_id;
    int points;
    int value;
    int num_of_goalkeepers;
    int num_of_team_players;
    int top_team_player_score;
    Player* top_team_player;
    AvlTree<int,Player*> players_by_id;
    AvlTree<Score ,Player*> players_by_score;
};


#endif //RATUV1_TEAM_H
