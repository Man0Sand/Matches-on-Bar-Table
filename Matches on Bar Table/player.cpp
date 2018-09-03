#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "player.h"

//----------------------------------------------------------------------------------------------------------------------------
// cl_player
//----------------------------------------------------------------------------------------------------------------------------
cl_player::cl_player(std::string player_type, std::string player_name):
m_matches_removed(0),
m_player_type(player_type),
m_player_name(player_name)
{
}

cl_player::~cl_player()
{
}

std::string cl_player::get_player_type()
{
	return m_player_type;
}

std::string cl_player::get_player_name()
{
	return m_player_name;
}

int cl_player::get_matches_removed()
{
    return m_matches_removed;
}

cl_player* cl_player::create(I_KeyboardBuffer& kb_buffer, const cl_player::T_config& player_config)
{
    if (player_config.type == HUMAN)
    {
        return new cl_player_human(kb_buffer, player_config.name);
    }
    if (player_config.type == COMPUTER)
    {
        return new cl_player_computer(player_config.name, player_config.difficulty);
    }
}

//----------------------------------------------------------------------------------------------------------------------------
// cl_player_computer
//----------------------------------------------------------------------------------------------------------------------------
static void swap_int(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline int rand_int_hi_lo(int upper, int lower)
{
    return((rand() % (upper - lower + 1)) + lower);
}

static int rand_int(int a, int b)
{
    if (b > a) swap_int(&a, &b);
    return rand_int_hi_lo(a, b);
}

cl_player_computer::cl_player_computer(std::string player_name, E_difficulty difficulty) :
    cl_player("computer", player_name),
    m_difficulty(difficulty)
{
}

int cl_player_computer::play_turn(int remaining_matches)
{
    srand(time(0));

    bool choose_randomly = determine_randomness(m_difficulty);
    int matches_to_remove = choose_matches(remaining_matches, choose_randomly);
    m_matches_removed += matches_to_remove;
    return matches_to_remove;
}

bool cl_player_computer::determine_randomness(E_difficulty difficulty)
{
    if (difficulty == EASY || (difficulty == MEDIUM && rand_int(0, 1) == 1))
    {
        return true;
    }

    return false;
}

int cl_player_computer::choose_matches_randomly(int matches_left)
{
    int matches_to_remove = rand_int(1, 3);

    while (matches_left < matches_to_remove)
    {
        --matches_to_remove;
    }

    return matches_to_remove;
}

int cl_player_computer::choose_matches_smartly(int matches_left)
{
    int matches_to_remove = 0;

    for (int i = 3; i > 0; --i)
    {
        matches_to_remove = i;
        if (!((matches_left - 1 - matches_to_remove) % 4))
        {
            break;
        }
    }

    return matches_to_remove;
}

int cl_player_computer::choose_matches(int matches_left, bool choose_randomly)
{
    if (choose_randomly)
    {
        return choose_matches_randomly(matches_left);
    }

    return choose_matches_smartly(matches_left);
}

//----------------------------------------------------------------------------------------------------------------------------
// cl_player_human
//----------------------------------------------------------------------------------------------------------------------------
cl_player_human::cl_player_human(I_KeyboardBuffer& kb_buffer, std::string player_name) :
cl_player("human", player_name),
kb_buffer_(kb_buffer)
{
}

int cl_player_human::play_turn(int remaining_matches)
{
    int matches_to_remove = 0;

    std::cout << "Give the number of matches (1-3) to remove.";
    
    while (matches_to_remove == 0 || matches_to_remove > remaining_matches)
    {
        matches_to_remove = pick_matches();
    }

    m_matches_removed += matches_to_remove;

    return matches_to_remove;
}

int cl_player_human::pick_matches()
{
    int user_input = kb_buffer_.WaitUntilInput({ keyboardbuffer::kOne, keyboardbuffer::kTwo, keyboardbuffer::kThree });
    
    if (user_input == keyboardbuffer::kOne)
    {
        return 1;
    }
    if (user_input == keyboardbuffer::kTwo)
    {
        return 2;
    }
    if (user_input == keyboardbuffer::kThree)
    {
        return 3;
    }
}
