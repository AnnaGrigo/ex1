
#include "Player.h"

Player::Player(int player_id, int team_id, int games_played, int goals, int cards, bool is_goalkeeper) {
    this->player_id = player_id;
    this->team_id = team_id;
    this->own_games_played = games_played;
    this->goals = goals;
    this->cards = cards;
    this->is_goalkeeper = is_goalkeeper;
    this->games_team_played = 0;
    this->my_team = nullptr;
    this->next_player_in_score = nullptr;
    this->prev_player_in_score = nullptr;
}

int Player::Get_Closest_Player(Player *player1, Player *player2) const {
    if (player1 == nullptr) {
        return player2->player_id;
    }
    if (player2 == nullptr) {
        return player1->player_id;
    }
    if (std::abs(this->goals - player1->goals) < std:: abs(this->goals - player2->goals)) {
        return player1->player_id;
    }
    if (std::abs(this->goals - player1->goals) > std:: abs(this->goals - player2->goals)) {
        return player2->player_id;
    }
    if (std::abs(this->cards - player1->cards) < std:: abs(this->cards - player2->cards)) {
        return player1->player_id;
    }
    if (std::abs(this->cards - player1->cards) > std:: abs(this->cards - player2->cards)) {
        return player2->player_id;
    }
    if (std::abs(this->player_id - player1->player_id) < std:: abs(this->player_id - player2->player_id)) {
        return player1->player_id;
    }
    if (std::abs(this->player_id - player1->player_id) > std:: abs(this->player_id - player2->player_id)) {
        return player2->player_id;
    }
    if(player1->player_id > player2->player_id) {
        return player1->player_id;
    }
    else {
        return player2->player_id;
    }
}


