#include "gtest/gtest.h"

#include "human_player.h"
#include "computer_player.h"
#include "match.h"
#include "matchpile.h"
#include "keyboard_buffer_mock.h"

#include "selector.h"

namespace
{
    TEST(SelectorTestInt, ForwardingAndReversing)
    {
        std::vector<int> nums = { 1, 2, 3, 5, 8 };
        Selector<int> selector = Selector<int>(&nums, &nums[2]);
        ASSERT_EQ(3, selector.GetValue());
        ASSERT_EQ(3, *selector.GetPointer());

        ++selector;
        ASSERT_EQ(5, selector.GetValue());
        ASSERT_EQ(5, *selector.GetPointer());

        ++selector;
        ASSERT_EQ(8, selector.GetValue());
        ASSERT_EQ(8, *selector.GetPointer());

        ++selector;
        ASSERT_EQ(1, selector.GetValue());
        ASSERT_EQ(1, *selector.GetPointer());

        ++selector;
        ASSERT_EQ(2, selector.GetValue());
        ASSERT_EQ(2, *selector.GetPointer());

        --selector;
        ASSERT_EQ(1, selector.GetValue());
        ASSERT_EQ(1, *selector.GetPointer());

        --selector;
        ASSERT_EQ(8, selector.GetValue());
        ASSERT_EQ(8, *selector.GetPointer());
    }

    TEST(SelectorTestInt, CopyConstructors)
    {
        std::vector<int> nums = { 1, 2, 3, 5, 8 };
        Selector<int> selector = Selector<int>(&nums, &nums[2]);
        ASSERT_EQ(3, selector.GetValue());

        Selector<int> selector2;
        selector2 = selector;

        ASSERT_EQ(3, selector2.GetValue());

        ++selector;

        Selector<int> selector3 = selector;
        ASSERT_EQ(5, selector3.GetValue());
    }
    
    TEST(SelectorTestInt, ConstructorFirstElement)
    {
        std::vector<int> nums = { 1, 2, 3, 5, 8 };
        Selector<int> selector = Selector<int>(&nums, &nums[0]);
        ASSERT_EQ(1, selector.GetValue());
    }
    TEST(SelectorTestInt, ConstructorSecondElement)
    {
        std::vector<int> nums = { 1, 2, 3, 5, 8 };
        Selector<int> selector = Selector<int>(&nums, &nums[1]);
        ASSERT_EQ(2, selector.GetValue());
    }

    TEST(SelectorTestInt, ConstructorThirdElement)
    {
        std::vector<int> nums = { 1, 2, 3, 5, 8 };
        Selector<int> selector = Selector<int>(&nums, &nums[2]);
        ASSERT_EQ(3, selector.GetValue());
    }

    TEST(SelectorTestInt, ConstructorFourthElement)
    {
        std::vector<int> nums = { 1, 2, 3, 5, 8 };
        Selector<int> selector = Selector<int>(&nums, &nums[3]);
        ASSERT_EQ(5, selector.GetValue());
    }

    TEST(SelectorTestInt, ConstructorLastElement)
    {
        std::vector<int> nums = { 1, 2, 3, 5, 8 };
        Selector<int> selector = Selector<int>(&nums, &nums[4]);
        ASSERT_EQ(8, selector.GetValue());
    }

    // A null pointer given to the class constructor
    TEST(SelectorTestInt, NullPointer1)
    {
        int num = 42;
        EXPECT_THROW(
            {
                try
        {
            Selector<int> selector = Selector<int>(nullptr, &num);
        }
        catch (const std::invalid_argument& e)
        {
            EXPECT_STREQ("Received a null pointer!", e.what());
            throw;
        }
            }, std::invalid_argument);
    }

    // Another null pointer given to the class constructor
    TEST(SelectorTestInt, NullPointer2)
    {
        std::vector<int> nums = { 1, 2, 3, 5, 8 };
        EXPECT_THROW(
            {
                try
        {
            Selector<int> selector = Selector<int>(&nums, nullptr);
        }
        catch (const std::invalid_argument& e)
        {
            EXPECT_STREQ("Received a null pointer!", e.what());
            throw;
        }
            }, std::invalid_argument);
    }

    // Empty vector given to the class constructor
    TEST(SelectorTestInt, EmptyContainer)
    {
        std::vector<int> empty;
        int num = 42;

        EXPECT_THROW(
            {
                try
        {
            Selector<int> selector = Selector<int>(&empty, &num);
        }
        catch (const std::invalid_argument& e)
        {
            EXPECT_STREQ("Received an empty container!", e.what());
            throw;
        }
            }, std::invalid_argument);
    }

    // A pointer that does not point to the container given to the constructor
    TEST(SelectorTestInt, InvalidInitialElement)
    {
        std::vector<int> nums = { 1, 2, 3, 5, 8 };
        int num = 42;
        EXPECT_THROW(
            {
                try
        {
            Selector<int> selector = Selector<int>(&nums, &num);
        }
        catch (const std::invalid_argument& e)
        {
            EXPECT_STREQ("Initial element does not point to given container!", e.what());
            throw;
        }
            }, std::invalid_argument);
    }

    TEST(SelectorTestMatch, Everything)
    {
        std::vector<bool> match_state_expected(4);
        std::vector<cl_match*> matches;
        for (int i = 0; i < 4; ++i)
        {
            matches.push_back(new cl_match());
        }
        Selector<cl_match*> selector(&matches, &matches[0]);

        match_state_expected = { false, false, false, false };
        for (unsigned int i = 0; i < matches.size(); ++i)
        {
            ASSERT_EQ(match_state_expected[i], matches[i]->is_removed());
        }

        ++selector;
        selector->remove();

        match_state_expected = { false, true, false, false };
        for (unsigned int i = 0; i < matches.size(); ++i)
        {
            ASSERT_EQ(match_state_expected[i], matches[i]->is_removed());
        }

        ++selector;
        ++selector;
        selector->remove();

        match_state_expected = { false, true, false, true };
        for (unsigned int i = 0; i < matches.size(); ++i)
        {
            ASSERT_EQ(match_state_expected[i], matches[i]->is_removed());
        }

        ++selector;
        selector->remove();

        match_state_expected = { true, true, false, true };
        for (unsigned int i = 0; i < matches.size(); ++i)
        {
            ASSERT_EQ(match_state_expected[i], matches[i]->is_removed());
        }

        --selector;
        --selector;
        selector->remove();

        match_state_expected = { true, true, true, true };
        for (unsigned int i = 0; i < matches.size(); ++i)
        {
            ASSERT_EQ(match_state_expected[i], matches[i]->is_removed());
        }
    }

    TEST(SelectorTestPlayer, Everything)
    {
        KeyboardBufferMock kb_buffer_mock = KeyboardBufferMock({keyboardbuffer::kThree, keyboardbuffer::kOne});
        cl_matchpile::MatchPileSettings pile_settings = { 2, cl_matchpile::NO };
        cl_matchpile match_pile = cl_matchpile(pile_settings);
        HumanPlayer human_player(kb_buffer_mock, "Pelimies", &match_pile);

        std::vector<Player*> players;
        players.push_back(&human_player);
        players.push_back(new ComputerPlayer("Tietsa", 42, Player::HARD, &match_pile));

        Selector<Player*> player_selector(&players, &players[0]);

        // Human's turn
        player_selector->play_turn();
        ASSERT_EQ(6, match_pile.get_remaining_matches());
        ASSERT_EQ(3, players[0]->get_matches_removed());
        ASSERT_EQ(0, players[1]->get_matches_removed());

        // Computer's turn
        ++player_selector;
        player_selector->play_turn();
        ASSERT_EQ(5, match_pile.get_remaining_matches());
        ASSERT_EQ(3, players[0]->get_matches_removed());
        ASSERT_EQ(1, players[1]->get_matches_removed());

        // Human's turn
        ++player_selector;
        player_selector->play_turn();
        ASSERT_EQ(4, match_pile.get_remaining_matches());
        ASSERT_EQ(4, players[0]->get_matches_removed());
        ASSERT_EQ(1, players[1]->get_matches_removed());

        // Computer's turn
        ++player_selector;
        player_selector->play_turn();
        ASSERT_EQ(1, match_pile.get_remaining_matches());
        ASSERT_EQ(4, players[0]->get_matches_removed());
        ASSERT_EQ(4, players[1]->get_matches_removed());
    }
}
