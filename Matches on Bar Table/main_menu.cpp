#include <iostream>

#include "main_menu.h"
#include "screen_buffer.h"
#include "I_keyboard_buffer.h"

MainMenu::MainMenu(I_KeyboardBuffer& kb_buffer):
kb_buffer_(kb_buffer),
player_settings_(   { cl_game::TWO,
                    {
                    { "Player 1", Player::HUMAN, Player::EASY },
                    { "Player 2", Player::HUMAN, Player::EASY },
                    { "Player 3", Player::HUMAN, Player::EASY },
                    { "Player 4", Player::HUMAN, Player::EASY }
                    }
                    }),
pile_settings_({ 3, cl_matchpile::NO }),
main_menu_items_({  new cl_menuitem_start_game("Start game", player_settings_, pile_settings_),
                    new cl_menuitem_player_settings("Player settings", &player_settings_),
                    new cl_menuitem_game_settings("Game settings", &pile_settings_),
                    new cl_menuitem("Exit game") }),
main_menu_(cl_menu(kb_buffer, &main_menu_items_, "Main menu"))
{
}

MainMenu::~MainMenu()
{
    for (cl_menuitem* p_menu_item : main_menu_items_)
    {
        delete p_menu_item;
    }
}

void MainMenu::run()
{
    show_intro_text();
    screenbuffer::ClearScreen();
    main_menu_.run_menu();
}

void MainMenu::show_intro_text()
{
    std::cout
        << std::endl
        << " -------------------------- " << std::endl
        << "|                          |" << std::endl
        << "| Matches On Bar Table 1.4 |" << std::endl
        << "|                          |" << std::endl
        << " -------------------------- " << std::endl
        << "Written by Veli-Matti Sainio." << std::endl << std::endl
        << "Players remove 1-3 matches from the table turn by turn." << std::endl
        << "The one who removes the last match is the loser." << std::endl << std::endl
        << "Press <Enter> to begin.";
    kb_buffer_.WaitUntilInput({ keyboardbuffer::kEnter });
}
