#include "gtest/gtest.h"
#include "cl_selector.h"

#include <vector>
#include "match.h"
#include "player.h"
#include "keyboard_buffer_mock.h"

namespace
{
    //------------------------------------------------------------------------------------------------------------------------
    // Tests for integers
    //------------------------------------------------------------------------------------------------------------------------
	TEST(cl_selector_test, IntegerConstructor1)
	{
        std::vector<int> nums = { 1, 2, 3, 5 };
        int* num;
        cl_selector_value<int> selector(&nums, &nums[0]);
        
        num = selector.next();
        ASSERT_EQ(2, *num);
        
        num = selector.previous();
        ASSERT_EQ(1, *num);
	}
    
    TEST(cl_selector_test, IntegerConstructor2)
	{
        std::vector<int> nums = { 1, 2, 3, 5 };
        int* num;
        cl_selector_value<int> selector(&nums, &nums[1]);
        
        num = selector.next();
        ASSERT_EQ(3, *num);
        
        num = selector.previous();
        ASSERT_EQ(2, *num);
	}

    TEST(cl_selector_test, IntegerConstructor3)
	{
        std::vector<int> nums = { 1, 2, 3, 5 };
        int* num;
        cl_selector_value<int> selector(&nums, &nums[2]);
        
        num = selector.previous();
        ASSERT_EQ(2, *num);
        
        num = selector.next();
        ASSERT_EQ(3, *num);
	}

    TEST(cl_selector_test, IntegerMultipleIncrements)
    {
        std::vector<int> nums = { 1, 2, 3, 5 };
        int* num;
        cl_selector_value<int> selector(&nums, &nums[0]);

        num = selector.next();
        ASSERT_EQ(2, *num);

        num = selector.next();
        ASSERT_EQ(3, *num);
    }

    TEST(cl_selector_test, IntegerMultipleDecrements)
    {
        std::vector<int> nums = { 1, 2, 3, 5 };
        int* num;
        cl_selector_value<int> selector(&nums, &nums[3]);

        num = selector.previous();
        ASSERT_EQ(3, *num);

        num = selector.previous();
        ASSERT_EQ(2, *num);
    }

	TEST(cl_selector_test, IntegerIncrementRollover)
	{
        std::vector<int> nums = { 1, 2, 3, 5 };
        int* num;
        cl_selector_value<int> selector(&nums, &nums[3]);

        num = selector.next();
        ASSERT_EQ(1, *num);
	}

    TEST(cl_selector_test, IntegerDecrementRollover)
    {
        std::vector<int> nums = { 1, 2, 3, 5 };
        int* num;
        cl_selector_value<int> selector(&nums, &nums[0]);

        num = selector.previous();
        ASSERT_EQ(5, *num);
    }

    //------------------------------------------------------------------------------------------------------------------------
    // Tests for cl_matches
    //------------------------------------------------------------------------------------------------------------------------
    TEST(cl_selector_test, Match)
    {
        cl_match* p_match;
        std::vector<bool> match_state_expected(4);
        std::vector<cl_match> matches(4);
        cl_selector<cl_match> selector(&matches, &matches[0]);

        match_state_expected = { false, false, false, false };
        for (unsigned int i = 0; i < matches.size(); ++i)
        {
            ASSERT_EQ(match_state_expected[i], matches[i].is_removed());
        }
        
        p_match = selector.next();
        p_match->remove();

        match_state_expected = { false, true, false, false };
        for (unsigned int i = 0; i < matches.size(); ++i)
        {
            ASSERT_EQ(match_state_expected[i], matches[i].is_removed());
        }

        p_match = selector.next();
        p_match = selector.next();
        p_match->remove();

        match_state_expected = { false, true, false, true };
        for (unsigned int i = 0; i < matches.size(); ++i)
        {
            ASSERT_EQ(match_state_expected[i], matches[i].is_removed());
        }

        p_match = selector.next();
        p_match->remove();

        match_state_expected = { true, true, false, true };
        for (unsigned int i = 0; i < matches.size(); ++i)
        {
            ASSERT_EQ(match_state_expected[i], matches[i].is_removed());
        }

        p_match = selector.previous();
        p_match = selector.previous();
        p_match->remove();

        match_state_expected = { true, true, true, true };
        for (unsigned int i = 0; i < matches.size(); ++i)
        {
            ASSERT_EQ(match_state_expected[i], matches[i].is_removed());
        }
    }

    //------------------------------------------------------------------------------------------------------------------------
    // Tests for cl_players
    //------------------------------------------------------------------------------------------------------------------------
    TEST(cl_selector_test, Player)
    {
        KeyboardBufferMock kb_keyboard_buffer_mock = KeyboardBufferMock({ keyboardbuffer::kThree, keyboardbuffer::kOne });
	    cl_player_human human_player(kb_keyboard_buffer_mock, "Pelimies");

        std::vector<cl_player*> players;
        players.push_back(&human_player);
        players.push_back(new cl_player_computer("Tietsa", cl_player::HARD));

        cl_selector<cl_player*> player_selector(&players, &players[0]);

        cl_player* p_active_player = players[0];
        
        int matches_left = 10;
        
        // Human's turn
        matches_left -= p_active_player->play_turn(matches_left);
        ASSERT_EQ(7, matches_left);
        ASSERT_EQ(3, players[0]->get_matches_removed());
        ASSERT_EQ(0, players[1]->get_matches_removed());

        // Computer's turn
        p_active_player = *player_selector.next();
        matches_left -= p_active_player->play_turn(matches_left);
        ASSERT_EQ(5, matches_left);
        ASSERT_EQ(3, players[0]->get_matches_removed());
        ASSERT_EQ(2, players[1]->get_matches_removed());

        // Human's turn
        p_active_player = *player_selector.next();
        matches_left -= p_active_player->play_turn(matches_left);
        ASSERT_EQ(4, matches_left);
        ASSERT_EQ(4, players[0]->get_matches_removed());
        ASSERT_EQ(2, players[1]->get_matches_removed());

        // Computer's turn
        p_active_player = *player_selector.next();
        matches_left -= p_active_player->play_turn(matches_left);
        ASSERT_EQ(1, matches_left);
        ASSERT_EQ(4, players[0]->get_matches_removed());
        ASSERT_EQ(5, players[1]->get_matches_removed());
    }
}