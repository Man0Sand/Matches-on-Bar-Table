#ifndef GAME_H
#define GAME_H

#include "matchpile.h"
#include "player.h"
#include <vector>
#include "selector.h"
#include "I_keyboard_buffer.h"

class cl_game
{
public:
    enum E_number_of_players
    {
        TWO = 2,
        THREE = 3,
        FOUR = 4
    };
    struct T_player_settings
    {
        E_number_of_players number_of_players;
        std::vector<cl_player::T_config> player_config;
    };   
    cl_game(I_KeyboardBuffer& kb_buffer, cl_matchpile* p_match_pile, std::vector<cl_player*> p_players);
    virtual ~cl_game();
    void play_game(void);
	cl_player* p_get_active_player();
	int get_turn();

private:
    // Variables
    I_KeyboardBuffer& kb_buffer_;
    int turn_;
    cl_matchpile* p_match_pile_;
    std::vector<cl_player*> p_players_;
    Selector<cl_player*> p_active_player_;

    // Functions
    void play_round(void);
    void choose_player(void);
	void show_game_over_message(void);
	virtual void prompt_for_enter();
};
#endif //GAME_H