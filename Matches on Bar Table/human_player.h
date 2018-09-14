#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include <string>

#include "player.h"

#include "I_keyboard_buffer.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(I_KeyboardBuffer& kb_buffer, std::string player_name, I_MatchPile* p_matchpile);

private:
    // Variables
    I_KeyboardBuffer & kb_buffer_;
    // Functions
    int choose_matches() override;
    int get_user_input();
};

#endif // HUMAN_PLAYER_H