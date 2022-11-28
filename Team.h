
#ifndef RATUV1_TEAM_H
#define RATUV1_TEAM_H

#include "AvlTree.h"
#include "Score.h"
#include "Player.h"


class Team {
public:
    int team_id;
    int points;
    int value;
    int num_of_goalkeepers;
    Score top_team_player_score;
    Player *top_team_player;
    AvlTree<int, Player *> team_players_by_id;
    AvlTree<Score, Player *> team_players_by_score;

    Team() = default;
    Team(int team_id, int points);
    ~Team() = default;

};

#endif //RATUV1_TEAM_H
