#include <iostream>
#include "game.h"

#include "screen_buffer.h"
#include "I_keyboard_buffer.h"

cl_game::cl_game(I_KeyboardBuffer& kb_buffer, const T_player_settings& player_settings, const cl_matchpile::MatchPileSettings& pile_settings) :
kb_buffer_(kb_buffer),
m_turn(0),
m_pile(pile_settings)
{
    for (int i = 0; i < player_settings.number_of_players; ++i)
    {
        m_p_players.push_back(cl_player::create(kb_buffer, player_settings.player_config[i]));
    }
    p_active_player_ = Selector<cl_player*>(&m_p_players, &m_p_players[0]);
}

cl_game::~cl_game()
{
    for (cl_player* p_player : m_p_players)
    {
        delete p_player;
    }
}

void cl_game::choose_player(void)
{
	if (1 < m_turn)
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
    screenbuffer::ClearScreen();
    while(m_pile.get_remaining_matches())
    {
		++m_turn;
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

    std::cout << m_pile.print_matches();
    
    int matches_to_remove = p_active_player_->play_turn(m_pile.get_remaining_matches());
    m_pile.remove_matches(matches_to_remove);

    screenbuffer::SetCursorPosition(0, last_row);
    std::cout << m_pile.print_matches();

    screenbuffer::ClearRow();

    if (!m_pile.get_remaining_matches())
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
	return m_turn;
}

void cl_game::prompt_for_enter()
{
    kb_buffer_.WaitUntilInput({ keyboardbuffer::kEnter });
}
