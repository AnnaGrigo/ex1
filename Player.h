
#ifndef RATUV1_PLAYER_H
#define RATUV1_PLAYER_H
#include "AvlTree.h"
#include "Team.h"

class Player
{
public:
    int player_id;
    int team_id;
    int own_games_played; //games played by this player when initialized
    int goals;
    int cards;
    bool is_goalkeeper;
    int games_team_played; //games played by the team when initialized
    Team *my_team;
    Player *next_player_in_score;
    Player *prev_player_in_score;

    Player() = default;
    Player(int player_id, int team_id, int games_played, int goals, int cards, bool is_goalkeeper);
    ~Player() = default;
};




#endif //RATUV1_PLAYER_H
