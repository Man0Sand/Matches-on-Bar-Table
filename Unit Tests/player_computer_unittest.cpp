#include "gtest/gtest.h"

#include <vector>

#include "computer_player.h"
#include "matchpile.h"
#include "match_pile_mock.h"
#include "keyboard_buffer_mock.h"
#include "keyboard_buffer.h"

namespace
{
	class ComputerPlayer_Test : public testing::Test
	{
	protected:
		virtual void SetUp()
		{
		}

		virtual void TearDown()
		{
		}

        int pick_match(int matches_before, ComputerPlayer::Difficulty difficulty)
        {
            MatchPileMock match_pile = MatchPileMock(matches_before);
            ComputerPlayer player = ComputerPlayer("Tietsa", 42, difficulty, &match_pile);
            Player* p_player = &player;
            p_player->play_turn();
            return matches_before - match_pile.get_remaining_matches();
        }

        void verify_match(int matches_before, int matches_picked_expected, ComputerPlayer::Difficulty difficulty)
        {
            int matches_picked = pick_match(matches_before, difficulty);
            ASSERT_EQ(matches_picked_expected, matches_picked);
        }

        void verify_match_statistical(int matches_before, std::vector<double> averages_expected, Player::Difficulty difficulty, std::string fail_msg)
        {
            double repeats = 1000.0;
            std::vector<double> occurrences_realized = { 0.0, 0.0, 0.0 };

            MatchPileMock pile = MatchPileMock(matches_before);
            ComputerPlayer player = ComputerPlayer("Tietsa", 42, difficulty, &pile);

            for (int i = 0; i < repeats; ++i)
            {
                pile.set_matches(matches_before);
                player.play_turn();
                int matches_picked = matches_before - pile.get_remaining_matches();
                occurrences_realized[matches_picked - 1] += 1.0;
            }

            std::vector<double> averages_realized = { 0.0, 0.0, 0.0 };
            for (unsigned int i = 0; i < occurrences_realized.size(); ++i)
            {
                averages_realized[i] = occurrences_realized[i] / repeats;
            }

            double allowed_deviation = 0.25;
            std::vector<double> allowed_deviations = { 0.0, 0.0, 0.0 };
            for (unsigned int i = 0; i < allowed_deviations.size(); ++i)
            {
                allowed_deviations[i] = allowed_deviation * averages_expected[i];
            }

            for (unsigned int i = 0; i < averages_realized.size(); ++i)
            {
                std::string fail_msg_complete = fail_msg + ", occurrence of " + std::to_string(i + 1) + " match(es)";
                ASSERT_NEAR(averages_expected[i], averages_realized[i], allowed_deviation*averages_expected[i]) << fail_msg_complete;
            }
        }

	};

    TEST_F(ComputerPlayer_Test, PickMatchesHard)
    {
        Player::Difficulty difficulty = Player::HARD;

        verify_match(1, 1, difficulty);
        verify_match(2, 1, difficulty);
        verify_match(3, 2, difficulty);
        verify_match(4, 3, difficulty);
        verify_match(5, 1, difficulty);
        verify_match(6, 1, difficulty);
        verify_match(7, 2, difficulty);
        verify_match(8, 3, difficulty);
        verify_match(9, 1, difficulty);
    }

    TEST_F(ComputerPlayer_Test, PickMatchesEasy)
    {
        Player::Difficulty difficulty = Player::EASY;

        verify_match_statistical(1, { 1.00, 0.00, 0.00 }, difficulty, "1 match left");
        verify_match_statistical(2, { 0.33, 0.67, 0.00 }, difficulty, "2 matches left");
        verify_match_statistical(3, { 0.33, 0.33, 0.33 }, difficulty, "3 matches left");
        verify_match_statistical(4, { 0.33, 0.33, 0.33 }, difficulty, "4 matches left");
        verify_match_statistical(5, { 0.33, 0.33, 0.33 }, difficulty, "5 matches left");
        verify_match_statistical(6, { 0.33, 0.33, 0.33 }, difficulty, "6 matches left");
        verify_match_statistical(7, { 0.33, 0.33, 0.33 }, difficulty, "7 matches left");
        verify_match_statistical(8, { 0.33, 0.33, 0.33 }, difficulty, "8 matches left");
        verify_match_statistical(9, { 0.33, 0.33, 0.33 }, difficulty, "9 matches left");
    }

    TEST_F(ComputerPlayer_Test, PickMatchesMedium)
    {
        Player::Difficulty difficulty = Player::MEDIUM;

        verify_match_statistical(1, { 1.00, 0.00, 0.00 }, difficulty, "1 match left");
        verify_match_statistical(2, { 0.67, 0.33, 0.00 }, difficulty, "2 matches left");
        verify_match_statistical(3, { 0.17, 0.67, 0.17 }, difficulty, "3 matches left");
        verify_match_statistical(4, { 0.17, 0.17, 0.67 }, difficulty, "4 matches left");
        verify_match_statistical(5, { 0.67, 0.17, 0.17 }, difficulty, "5 matches left");
        verify_match_statistical(6, { 0.67, 0.17, 0.17 }, difficulty, "6 matches left");
        verify_match_statistical(7, { 0.17, 0.67, 0.17 }, difficulty, "7 matches left");
        verify_match_statistical(8, { 0.17, 0.17, 0.67 }, difficulty, "8 matches left");
        verify_match_statistical(9, { 0.67, 0.17, 0.17 }, difficulty, "9 matches left");
    }

    TEST(ComputerRandomizerTest, TestMatchCount)
    {
        ComputerRandomizer randomizer = ComputerRandomizer(42);
        
        std::vector<int> nums(3);
        for (int i = 0; i < 1000; ++i)
        {
            int match_count = randomizer.match_count();
            ++nums[match_count - 1];
        }

        ASSERT_NEAR(333, nums[0], 33);
        ASSERT_NEAR(333, nums[1], 33);
        ASSERT_NEAR(333, nums[2], 33);
    }

    TEST(ComputerRandomizerTest, TestRandomness)
    {
        ComputerRandomizer randomizer = ComputerRandomizer(42);

        std::vector<int> bools(2);
        for (int i = 0; i < 1000; ++i)
        {
            if (randomizer.randomness())
            {
                ++bools[1];
            }
            else
            {
                ++bools[0];
            }
        }
        
        ASSERT_NEAR(500, bools[0], 50);
        ASSERT_NEAR(500, bools[1], 50);
    }

}	//namespace