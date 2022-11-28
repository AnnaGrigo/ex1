
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

