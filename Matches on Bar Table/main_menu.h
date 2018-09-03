#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "game.h"
#include "menu.h"

#include "I_keyboard_buffer.h"

class MainMenu
{
public:
    MainMenu(I_KeyboardBuffer& kb_buffer);
    ~MainMenu();
    void run();

private:
    I_KeyboardBuffer& kb_buffer_;
    cl_game::T_player_settings player_settings_;
    cl_matchpile::MatchPileSettings pile_settings_;
    std::vector<cl_menuitem*> main_menu_items_;
    cl_menu main_menu_;
    void show_intro_text();
};

#endif // MAIN_MENU_H