#include "computer_player.h"

ComputerPlayer::ComputerPlayer(std::string player_name, unsigned randomizer_seed, Difficulty difficulty, I_MatchPile* p_match_pile) :
    Player("computer", player_name, p_match_pile),
    difficulty_(difficulty),
    randomizer_(randomizer_seed)
{
}

int ComputerPlayer::choose_matches()
{
    return pick_matches(p_match_pile_->get_remaining_matches(), determine_randomness());
}

bool ComputerPlayer::determine_randomness()
{
    if (difficulty_ == EASY || (difficulty_ == MEDIUM && randomizer_.randomness()))
    {
        return true;
    }

    return false;
}

int ComputerPlayer::pick_matches(int matches_left, bool choose_randomly)
{
    int matches_to_remove = 0;

    if (choose_randomly)
    {
        matches_to_remove = randomizer_.match_count();

        while (matches_left < matches_to_remove)
        {
            --matches_to_remove;
        }
    }
    else
    {
        for (int i = 3; i > 0; --i)
        {
            matches_to_remove = i;
            if (!((matches_left - 1 - matches_to_remove) % 4))
            {
                break;
            }
        }
    }
    return matches_to_remove;
}