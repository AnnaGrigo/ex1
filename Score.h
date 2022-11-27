
#ifndef RATUV1_SCORE_H
#define RATUV1_SCORE_H

class Score
{
public:
    int goals;
    int tickets;
    int games_played;

    Score() = default;
    Score(int new_goals, int new_tickets, int new_games_played)
            : goals(new_goals)
            , tickets(new_tickets)
            , games_played(new_games_played)
    {
    }
    Score(const Score &other)
    {
        this->goals = other.goals;
        this->tickets = other.tickets;
        this->games_played = other.games_played;
    }

    friend bool operator<(Score score1, Score score2)
    {
        if (score1.goals != score2.goals)
        {
            return score1.goals < score2.goals;
        }
        if (score1.tickets != score2.tickets)
        {
            return score1.tickets < score2.tickets;
        }
        return score1.games_played < score2.games_played;
    }
};

#endif //RATUV1_SCORE_H
