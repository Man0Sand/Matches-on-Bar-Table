#include "menuitems.h"
#include "menu.h"
#include "user_IO.h"
#include "screen_buffer.h"

#include "player.h"
#include "game.h"
#include "keyboard_buffer.h"

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem
//----------------------------------------------------------------------------------------------------------------------------
cl_menuitem::cl_menuitem(std::string display_text) :
	m_display_text(display_text)
{
}

cl_menuitem::~cl_menuitem()
{
}

bool cl_menuitem::enter_pressed()
{
	return true;
}

std::string cl_menuitem::get_display_text()
{
	return m_display_text;
}

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem_edit
//----------------------------------------------------------------------------------------------------------------------------
cl_menuitem_edit::cl_menuitem_edit(std::string static_text, std::string* p_text_under_edit) :
	cl_menuitem(static_text + ": " + *p_text_under_edit),
	m_p_text_under_edit(p_text_under_edit),
	m_static_text(static_text)
{
}

bool cl_menuitem_edit::enter_pressed()
{
	user_IO::get_user_input(m_p_text_under_edit);
	m_display_text = m_static_text + ": " + *m_p_text_under_edit;
	return false;
}

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem_edit_player
//----------------------------------------------------------------------------------------------------------------------------
cl_menuitem_edit_player::cl_menuitem_edit_player(std::string display_text, cl_player::T_config* player_cfg) :
	cl_menuitem(display_text),
	m_p_player_cfg(player_cfg),
	m_display_text(display_text)
{
}

bool cl_menuitem_edit_player::enter_pressed()
{
	std::vector<cl_menuitem*> p_edit_player_items;
	
    // Menu item for editing player name
    p_edit_player_items.push_back(new cl_menuitem_edit("Name", &m_p_player_cfg->name));
    
    // Menu item for toggling player type
    std::vector<cl_player::E_type> player_type_enums = { cl_player::HUMAN, cl_player::COMPUTER};
    std::vector<std::string> player_type_texts = { "human", "computer" };
    p_edit_player_items.push_back(new cl_menuitem_toggle<cl_player::E_type>("Type", &player_type_enums, &player_type_texts, &m_p_player_cfg->type));

    // Menu item for toggling computer difficulty level
    std::vector<cl_player::E_difficulty> difficulty_enums = { cl_player::EASY, cl_player::MEDIUM, cl_player::HARD };
    std::vector<std::string> difficulty_texts = { "easy", "medium", "hard" };
    p_edit_player_items.push_back(new cl_menuitem_toggle< cl_player::E_difficulty >("Difficulty", &difficulty_enums, &difficulty_texts, &m_p_player_cfg->difficulty));

	// Menu item for exiting the menu
    p_edit_player_items.push_back(new cl_menuitem("Exit menu"));

	cl_menu icl_menu(KeyboardBuffer::GetInstance(), &p_edit_player_items, m_display_text);
	icl_menu.run_menu();

	for (cl_menuitem* p_menu_item : p_edit_player_items)
	{
		delete p_menu_item;
	}

	return false;
}

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem_player_settings
//----------------------------------------------------------------------------------------------------------------------------
cl_menuitem_player_settings::cl_menuitem_player_settings(std::string display_text, cl_game::T_player_settings* p_player_settings) :
	cl_menuitem(display_text),
	m_p_player_cfg(&p_player_settings->player_config),
	m_p_number_of_players(&p_player_settings->number_of_players)
{
}

bool cl_menuitem_player_settings::enter_pressed()
{
	std::vector<cl_menuitem*> p_player_settings_items;
	
    std::vector<cl_game::E_number_of_players> number_of_player_enums = { cl_game::TWO, cl_game::THREE, cl_game::FOUR };
    std::vector<std::string> number_of_players_texts = { "2", "3", "4" };
    p_player_settings_items.push_back(new cl_menuitem_toggle<cl_game::E_number_of_players>("Number of players", &number_of_player_enums, &number_of_players_texts, m_p_number_of_players));
	p_player_settings_items.push_back(new cl_menuitem_edit_player("Edit player 1", &(*m_p_player_cfg)[0]));
	p_player_settings_items.push_back(new cl_menuitem_edit_player("Edit player 2", &(*m_p_player_cfg)[1]));
	p_player_settings_items.push_back(new cl_menuitem_edit_player("Edit player 3", &(*m_p_player_cfg)[2]));
	p_player_settings_items.push_back(new cl_menuitem_edit_player("Edit player 4", &(*m_p_player_cfg)[3]));
	p_player_settings_items.push_back(new cl_menuitem("Exit menu"));

	cl_menu icl_menu_player_settings(KeyboardBuffer::GetInstance(), &p_player_settings_items, "Player settings");
	icl_menu_player_settings.run_menu();

	for (cl_menuitem* p_menuitem : p_player_settings_items)
	{
		delete p_menuitem;
	}

	return false;
}

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem_game_settings
//----------------------------------------------------------------------------------------------------------------------------
cl_menuitem_game_settings::cl_menuitem_game_settings(std::string display_text, cl_matchpile::MatchPileSettings* p_pile_settings) :
	cl_menuitem(display_text),
    m_p_pick_matches_randomly(&p_pile_settings->pick_matches_randomly)
{
}

bool cl_menuitem_game_settings::enter_pressed()
{
	std::vector<cl_menuitem*> p_player_settings_items;

    std::vector<cl_matchpile::e_pick_matches_randomly> pick_matches_randomly_enums = { cl_matchpile::NO, cl_matchpile::YES };
    std::vector<std::string> pick_matches_randomly_texts = { "No", "Yes" };
    p_player_settings_items.push_back(new cl_menuitem_toggle<cl_matchpile::e_pick_matches_randomly>("Pick matches randomly", &pick_matches_randomly_enums, &pick_matches_randomly_texts, m_p_pick_matches_randomly));
	
    p_player_settings_items.push_back(new cl_menuitem("Exit menu"));

	cl_menu icl_menu_game_settings(KeyboardBuffer::GetInstance(), &p_player_settings_items, "Game settings");
	icl_menu_game_settings.run_menu();

	for (cl_menuitem* p_menuitem : p_player_settings_items)
	{
		delete p_menuitem;
	}

	return false;
}

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem_start_game
//----------------------------------------------------------------------------------------------------------------------------
cl_menuitem_start_game::cl_menuitem_start_game(std::string display_text, const cl_game::T_player_settings& player_settings, const cl_matchpile::MatchPileSettings& pile_settings) :
    cl_menuitem(display_text),
    m_player_settings(player_settings),
    pile_settings_(pile_settings)
{
}

bool cl_menuitem_start_game::enter_pressed()
{
    cl_matchpile match_pile = cl_matchpile(pile_settings_);

    std::vector<cl_player*> p_players(m_player_settings.number_of_players);
    for (int i = 0; i < m_player_settings.number_of_players; ++i)
    {
        p_players[i] = cl_player::create(KeyboardBuffer::GetInstance(), m_player_settings.player_config[i]);
    }
    
    cl_game game(KeyboardBuffer::GetInstance(), &match_pile, p_players);
	game.play_game();
	
    for (cl_player* player : p_players)
    {
        delete player;
    }
    
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem_toggle
//----------------------------------------------------------------------------------------------------------------------------
template <typename T>
cl_menuitem_toggle<T>::cl_menuitem_toggle(std::string static_text, std::vector<T>* p_selection_enums, std::vector<std::string>* p_selection_texts, T* p_active_selection):
cl_menuitem(static_text),
m_p_active_selection(p_active_selection),
m_static_text(static_text),
m_menuitem_value_selection(p_selection_enums, m_p_active_selection)
{
    for (unsigned int i = 0; i < p_selection_enums->size(); ++i)
    {
        m_text_mappings[(*p_selection_enums)[i]] = (*p_selection_texts)[i];
    }
    m_display_text = m_static_text + ": " + m_text_mappings[*m_p_active_selection];
}

template <typename T>
bool cl_menuitem_toggle<T>::enter_pressed()
{
    *m_p_active_selection = *m_menuitem_value_selection.next();
    m_display_text = m_static_text + ": " + m_text_mappings[*m_p_active_selection];

	return false;
}

template class cl_menuitem_toggle<cl_player::E_difficulty>;
template class cl_menuitem_toggle<cl_game::E_number_of_players>;
template class cl_menuitem_toggle<cl_player::E_type>;
template class cl_menuitem_toggle<cl_matchpile::e_pick_matches_randomly>;
