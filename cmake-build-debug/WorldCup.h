//
// Created by annag on 19/11/2022.
//
#include "AvlTree.h"

#ifndef EX1_WORLDCUP_H
#define EX1_WORLDCUP_H

class WorldCup{
public:
    AvlTree<int ,Player> players;
    AvlTree<int ,Team> teams;
};

class Team{

};

class Player{
public:
    int playerId;
    int TeamId;
    int GamesPlayed;
    int Goals;
    int Cards;
    bool GoalKeeper;




};


#endif //EX1_WORLDCUP_H
