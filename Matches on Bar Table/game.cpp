#include <iostream>
#include "game.h"

#include "screen_buffer.h"

cl_game::cl_game(I_KeyboardBuffer& kb_buffer, I_MatchPile* p_match_pile, std::vector<cl_player*> p_players) :
kb_buffer_(kb_buffer),
turn_(0),
p_match_pile_(p_match_pile),
p_players_(p_players),
p_active_player_(&p_players_, &p_players_[0])
{
}

cl_game::~cl_game()
{
    for (cl_player* p_player : p_players_)
    {
        delete p_player;
    }
}

void cl_game::choose_player(void)
{
	if (1 < turn_)
	{
        ++p_active_player_;
	}
}

void cl_game::show_game_over_message(void)
{
    std::cout << p_active_player_->get_player_name() << " (" << p_active_player_->get_player_type() << ") loses!\n";
    std::cout << "\nPress <Enter> to return to main menu.\n";
	prompt_for_enter();
}

void cl_game::play_game(void)
{
    while(p_match_pile_->get_remaining_matches())
    {
		++turn_;
		choose_player();
        play_round();
    }
	
	show_game_over_message();
}

void cl_game::play_round(void)
{
    screenbuffer::ClearScreen();
    std::cout << p_active_player_->get_player_name() << "'s ("
        << p_active_player_->get_player_type() << ") turn.\n\n";

    int last_row = screenbuffer::GetCursorRow(); 

    std::cout << p_match_pile_->print_matches();
    
    p_active_player_->play_turn();

    screenbuffer::SetCursorPosition(0, last_row);
    std::cout << p_match_pile_->print_matches();

    screenbuffer::ClearRow();

    if (!p_match_pile_->get_remaining_matches())
    {
        return;
    }

    std::cout << "Press <Enter> for next player's turn.";
	prompt_for_enter();
}

cl_player* cl_game::p_get_active_player()
{
    return p_active_player_.GetValue();
}

int cl_game::get_turn()
{
	return turn_;
}

void cl_game::prompt_for_enter()
{
    kb_buffer_.WaitUntilInput({ keyboardbuffer::kEnter });
}
