#include <iostream>

#include "player.h"
#include "computer_player.h"
#include "human_player.h"

Player::Player(std::string player_type, std::string player_name, I_MatchPile* p_match_pile):
p_match_pile_(p_match_pile),
matches_removed_(0),
player_type_(player_type),
player_name_(player_name)
{
}

Player::~Player()
{
}

std::string Player::get_player_type()
{
	return player_type_;
}

std::string Player::get_player_name()
{
	return player_name_;
}

int Player::get_matches_removed()
{
    return matches_removed_;
}

void Player::play_turn()
{
    int matches_to_remove = choose_matches();
    matches_removed_ += matches_to_remove;
    p_match_pile_->remove_matches(matches_to_remove);
}

Player* Player::create(I_KeyboardBuffer& kb_buffer, unsigned randomizer_seed, const Player::Config& player_config, I_MatchPile* p_match_pile)
{
    if (player_config.type == HUMAN)
    {
        return new HumanPlayer(kb_buffer, player_config.name, p_match_pile);
    }
    if (player_config.type == COMPUTER)
    {
        return new ComputerPlayer(player_config.name, randomizer_seed, player_config.difficulty, p_match_pile);
    }
}
