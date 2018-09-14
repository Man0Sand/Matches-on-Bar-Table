#include <iostream>

#include "human_player.h"

HumanPlayer::HumanPlayer(I_KeyboardBuffer& kb_buffer, std::string player_name, I_MatchPile* p_matchpile) :
    Player("human", player_name, p_matchpile),
    kb_buffer_(kb_buffer)
{
}

int HumanPlayer::choose_matches()
{
    int matches_to_remove = 0;

    std::cout << "Give the number of matches (1-3) to remove.";

    while (matches_to_remove <= 0 || p_match_pile_->get_remaining_matches() < matches_to_remove)
    {
        matches_to_remove = get_user_input();
    }

    return matches_to_remove;
}

int HumanPlayer::get_user_input()
{
    int user_input = kb_buffer_.WaitUntilInput({ keyboardbuffer::kOne, keyboardbuffer::kTwo, keyboardbuffer::kThree });

    if (user_input == keyboardbuffer::kOne)
    {
        return 1;
    }
    if (user_input == keyboardbuffer::kTwo)
    {
        return 2;
    }
    if (user_input == keyboardbuffer::kThree)
    {
        return 3;
    }
}
