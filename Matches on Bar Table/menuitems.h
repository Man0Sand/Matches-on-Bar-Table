#ifndef MENUITEMS_H
#define MENUITEMS_H

#include <string>
#include <vector>
#include <map>

#include "player.h"
#include "cl_selector.h"
#include "game.h"
#include "matchpile.h"

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem
//----------------------------------------------------------------------------------------------------------------------------
class cl_menuitem
{
public:
	cl_menuitem(std::string display_text);
	virtual ~cl_menuitem();
	virtual bool enter_pressed();
	std::string get_display_text();

protected:
	std::string m_display_text;
};

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem_edit
//----------------------------------------------------------------------------------------------------------------------------
class cl_menuitem_edit : public cl_menuitem
{
public:
	cl_menuitem_edit(std::string static__text, std::string* p_text_under_edit);
	bool enter_pressed();

private:
	std::string* m_p_text_under_edit;
	const std::string m_static_text;
};

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem_edit_player
//----------------------------------------------------------------------------------------------------------------------------
class cl_menuitem_edit_player : public cl_menuitem
{
public:
	cl_menuitem_edit_player(std::string display_text, Player::Config* player_cfg);
	bool enter_pressed();

private:
    Player::Config* m_p_player_cfg;
	const std::string m_display_text;
};

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem_player_settings
//----------------------------------------------------------------------------------------------------------------------------
class cl_menuitem_player_settings : public cl_menuitem
{
public:
	cl_menuitem_player_settings(std::string display_text, cl_game::T_player_settings* p_player_settings);
	bool enter_pressed();

private:
	std::vector<Player::Config>* m_p_player_cfg;
	cl_game::E_number_of_players* m_p_number_of_players;
};

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem_game_settings
//----------------------------------------------------------------------------------------------------------------------------
class cl_menuitem_game_settings : public cl_menuitem
{
public:
	cl_menuitem_game_settings(std::string display_text, cl_matchpile::MatchPileSettings* p_pile_settings);
	bool enter_pressed();

private:
	cl_matchpile::e_pick_matches_randomly* m_p_pick_matches_randomly;
};

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem_start_game
//----------------------------------------------------------------------------------------------------------------------------
class cl_menuitem_start_game : public cl_menuitem
{
public:
	cl_menuitem_start_game(std::string display_text, const cl_game::T_player_settings& player_settings, const cl_matchpile::MatchPileSettings& pile_settings);
	bool enter_pressed();

private:
    const cl_game::T_player_settings& m_player_settings;
    const cl_matchpile::MatchPileSettings& pile_settings_;
};

//----------------------------------------------------------------------------------------------------------------------------
// cl_menuitem_toggle
//----------------------------------------------------------------------------------------------------------------------------
template <typename T>
class cl_menuitem_toggle : public cl_menuitem
{
public:
	cl_menuitem_toggle(std::string static_text, std::vector<T>* p_selection_enums, std::vector<std::string>* p_selection_texts, T* p_active_selection);
	bool enter_pressed();

private:
	T* m_p_active_selection;
	std::string m_static_text;
    cl_selector_value<T> m_menuitem_value_selection;
    std::map<T, std::string> m_text_mappings;
};

#endif // MENUITEMS_H
