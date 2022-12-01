#ifndef RATUV1_TEAM_H
#define RATUV1_TEAM_H

#include "AvlTree.h"
#include "Score.h"

class Player;

class Team {
public:
    int team_id;
    int points;
    int value;
    int num_of_goalkeepers;
    int all_team_games_played;
    Score top_team_player_score;
    Player *top_team_player;
    AvlTree<int, Player *> team_players_by_id;
    AvlTree<Score, Player *> team_players_by_score;

    Team() = default;
    Team(int team_id, int points);
    ~Team() = default;

};

bool Is_Team_Legal(Team* );

#endif //RATUV1_TEAM_H