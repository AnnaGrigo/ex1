
#ifndef RATUV1_WORLDCUP_H
#define RATUV1_WORLDCUP_H

#include "AvlTree.h"
#include "Player.h"
#include "Team.h"
#include "Score.h"

class WorldCup
{
public:
    AvlTree<int, Team*> teams_by_id;
    AvlTree<int, Team*> legal_teams_by_id;
    AvlTree<int, Player*> all_players_by_id;
    AvlTree<Score, Player*> all_players_by_score;
    Score top_player_score;
    Player* top_player;


    WorldCup();
    ~WorldCup();
    StatusType AddTeam(int teamID, int points);
    StatusType RemoveTeam(int teamID);
    StatusType AddPlayer(int playerID, int teamID, int GamesPlayed, int goals,
                         int cards, bool isGoalkeeper);
    StatusType RemovePlayer(int playerID);
    StatusType UpdatePlayer(int playerID,int gamesPlayed, int ScoredGoals, int CardsReceived);
    StatusType PlayMatch(int teamID1, int teamID2);
    output_t<int> GetNumPlayedGames(int playerID);
    output_t<int> GetTeamPoints(int teamID);
    StatusType UniteTeams(int teamID1, int teamID2, int NewTeamId);
    output_t<int> GetTopScorer(int teamID);
    output_t<int> GetAllPlayersCount(int teamID);
    StatusType GetAllPlayers(int teamID, int *const output);
    output_t<int> GetClosestPlayer(int playerID, int teamID);
    output_t<int> KnockoutWinner(int MinTeamID, int MaxTeamID);
};

#endif //RATUV1_WORLDCUP_H
