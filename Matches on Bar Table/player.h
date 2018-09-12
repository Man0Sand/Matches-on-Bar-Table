#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "I_match_pile.h"
#include "I_keyboard_buffer.h"

class cl_player
{
public:
    void play_turn();
    virtual ~cl_player();
    std::string get_player_type();
    std::string get_player_name();
    int get_matches_removed();
    enum E_type
    {
        HUMAN,
        COMPUTER
    };
    enum E_difficulty
    {
        EASY,
        MEDIUM,
        HARD
    };
    struct T_config
    {
        std::string name;
        E_type type;
        E_difficulty difficulty;
    };
    static cl_player* create(I_KeyboardBuffer& kb_buffer, const T_config& player_config, I_MatchPile* p_match_pile);

protected:
    // Variables
    I_MatchPile* p_match_pile_;
    int m_matches_removed;
    const std::string m_player_type;
    const std::string m_player_name;
    
    // Functions
    virtual int choose_matches() = 0;
    cl_player(std::string player_type, std::string player_name, I_MatchPile* p_match_pile);
 };

class cl_player_computer : public cl_player
{
public:
    cl_player_computer(std::string player_name, E_difficulty difficulty, I_MatchPile* p_match_pile);
    bool determine_randomness(E_difficulty difficulty);

private:
    // Variables
    const E_difficulty m_difficulty;
    // Functions
    int choose_matches() override;
    int pick_matches(int matches_left, bool choose_randomly);
};

class cl_player_human : public cl_player
{
public:
    cl_player_human(I_KeyboardBuffer& kb_buffer, std::string player_name, I_MatchPile* p_matchpile);

private:
    // Variables
    I_KeyboardBuffer& kb_buffer_;
    // Functions
    int choose_matches() override;
    int get_user_input();
};

#endif // PLAYER_H