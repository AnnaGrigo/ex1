
#ifndef RATUV1_SCORE_H
#define RATUV1_SCORE_H

class Score
{
public:
    int goals;
    int cards;
    int player_id;

    Score() : goals(0), cards(0), player_id(0) {}
    Score(int new_goals, int new_cards, int new_player_id)
            : goals(new_goals)
            , cards(new_cards)
            , player_id(new_player_id)
    {
    }
    Score(const Score &other)
    {
        this->goals = other.goals;
        this->cards = other.cards;
        this->player_id = other.player_id;
    }

    friend bool operator<(const Score& score1, const Score& score2)
    {
        if (score1.goals != score2.goals)
        {
            return score1.goals < score2.goals;
        }
        if (score1.cards != score2.cards)
        {
            return score1.cards > score2.cards;
        }
        return score1.player_id < score2.player_id;
    }

    friend bool operator>(const Score& score1, const Score& score2)
    {
        if (score1.goals != score2.goals)
        {
            return score1.goals > score2.goals;
        }
        if (score1.cards != score2.cards)
        {
            return score1.cards < score2.cards;
        }
        return score1.player_id > score2.player_id;
    }

    friend bool operator==(const Score& score1, const Score& score2)
    {
        return score1.goals == score2.goals && score1.cards == score2.cards && score1.player_id == score2.player_id;
    }

    friend bool operator<=(const Score& score1, const Score& score2)
    {
        return score1 < score2 || score1 == score2;
    }

    friend bool operator>=(const Score& score1, const Score& score2)
    {
        return score1 > score2 || score1 == score2;
    }

    
};

#endif //RATUV1_SCORE_H
