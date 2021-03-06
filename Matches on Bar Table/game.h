#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <vector>
#include "selector.h"
#include "I_keyboard_buffer.h"
#include "I_match_pile.h"

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
        std::vector<Player::Config> player_config;
    };   
    cl_game(I_KeyboardBuffer& kb_buffer, I_MatchPile* p_match_pile, std::vector<Player*> p_players);
    virtual ~cl_game();
    void play_game(void);
	Player* p_get_active_player();
	int get_turn();

private:
    // Variables
    I_KeyboardBuffer& kb_buffer_;
    int turn_;
    I_MatchPile* p_match_pile_;
    std::vector<Player*> p_players_;
    Selector<Player*> p_active_player_;

    // Functions
    void play_round(void);
    void choose_player(void);
	void show_game_over_message(void);
	virtual void prompt_for_enter();
};
#endif //GAME_H