
#ifndef RATUV1_PLAYER_H
#define RATUV1_PLAYER_H
#include "AvlTree.h"
#include "Team.h"

class Player
{
public:
    int player_id;
    int team_id;
    int own_games_played;
    int goals;
    int tickets;
    bool is_goalkeeper;
    int games_team_played;
    Team *my_team;
    Player *next_player_in_score;
    Player *prev_player_in_score;
};


#endif //RATUV1_PLAYER_H
