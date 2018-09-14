#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "player.h"

#include "computer_randomizer.h"

class ComputerPlayer : public Player
{
public:
    ComputerPlayer(std::string player_name, unsigned randomizer_seed, Difficulty difficulty, I_MatchPile* p_match_pile);
    bool determine_randomness();

private:
    // Variables
    const Difficulty difficulty_;
    ComputerRandomizer randomizer_;
    // Functions
    int choose_matches() override;
    int pick_matches(int matches_left, bool choose_randomly);
};

#endif // COMPUTER_PLAYER_H
