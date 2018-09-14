#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "I_keyboard_buffer.h"
#include "I_match_pile.h"

class Player
{
public:
    void play_turn();
    virtual ~Player();
    std::string get_player_type();
    std::string get_player_name();
    int get_matches_removed();
    enum Type
    {
        HUMAN,
        COMPUTER
    };
    enum Difficulty
    {
        EASY,
        MEDIUM,
        HARD
    };
    struct Config
    {
        std::string name;
        Type type;
        Difficulty difficulty;
    };
    static Player* create(I_KeyboardBuffer& kb_buffer, unsigned randomizer_seed, const Config& player_config, I_MatchPile* p_match_pile);

protected:
    // Variables
    I_MatchPile* p_match_pile_;
    int matches_removed_;
    const std::string player_type_;
    const std::string player_name_;
    
    // Functions
    virtual int choose_matches() = 0;
    Player(std::string player_type, std::string player_name, I_MatchPile* p_match_pile);
 };

#endif // PLAYER_H