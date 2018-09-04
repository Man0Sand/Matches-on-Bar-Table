#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "I_match_pile.h"
#include "I_keyboard_buffer.h"

class cl_player
{
public:
    virtual int play_turn(int remaining_matches) = 0;
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
    I_MatchPile * p_match_pile_;
    int m_matches_removed;
    const std::string m_player_type;
    const std::string m_player_name;
    cl_player(std::string player_type, std::string player_name, I_MatchPile* p_match_pile);
 };

class cl_player_computer : public cl_player
{
public:
    cl_player_computer(std::string player_name, E_difficulty difficulty, I_MatchPile* p_match_pile);
    int play_turn(int remaining_matches);
    bool determine_randomness(E_difficulty difficulty);
    int choose_matches(int matches_left, bool choose_randomly);
    int choose_matches_randomly(int matches_left);
    int choose_matches_smartly(int matches_left);

private:
    const E_difficulty m_difficulty;
};

class cl_player_human : public cl_player
{
public:
    cl_player_human(I_KeyboardBuffer& kb_buffer, std::string player_name, I_MatchPile* p_matchpile);
    int pick_matches();
    int play_turn(int remaining_matches);
private:
    I_KeyboardBuffer& kb_buffer_;
};

#endif // PLAYER_H