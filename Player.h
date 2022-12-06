
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
    int Get_Closest_Player(Player* player1, Player* player2) const;
};

/*
template <class Key, class Value>
void limitedInorderHelper(AvlNode<Key, Value> *root, Pair<Key, Value> arr[], Key minKey, Key maxKey ,int& index){
    if (!root)
    {
        return;
    }
    if((root->key < minKey || root->key > maxKey) && (!findNodeInRange(root->left_son,minKey,maxKey)) || (!findNodeInRange(root->right_son,minKey,maxKey))){
        return;
    }
    if(findNodeInRange(root->left_son,minKey,maxKey)){
        limitedInorderHelper(root->left_son,arr,minKey,maxKey,index);
    }
    if(root->key <= maxKey && minKey <=root->key){
        arr[index].key = root->key;
        arr[index].value = root->value;
        index++;
        if (findNodeInRange(root->right_son,minKey,maxKey)){
            limitedInorderHelper(root->right_son,arr,minKey,maxKey,index);
        }
    }
}*/
#endif //RATUV1_PLAYER_H
