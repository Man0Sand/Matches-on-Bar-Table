#include "gtest/gtest.h"
#include "player.h"

namespace
{
	// Constants
	std::string PlayerName = "Tietsari";
	cl_player::E_difficulty Difficulty = cl_player::HARD;

	class ComputerPlayer_Test : public testing::Test
	{
	protected:
		virtual void SetUp()
		{
            p_match_pile = new cl_matchpile(pile_settings);
            p_Computer = new cl_player_computer(PlayerName, Difficulty, p_match_pile);
		}

		virtual void TearDown()
		{
			delete p_Computer;
            delete p_match_pile;
		}

		cl_player_computer* p_Computer;
        cl_matchpile* p_match_pile;
        cl_matchpile::MatchPileSettings pile_settings = { 2, cl_matchpile::NO };

	};

	TEST_F(ComputerPlayer_Test, Constructor)
	{
		ASSERT_EQ("Tietsari", p_Computer->get_player_name());
		ASSERT_EQ("computer", p_Computer->get_player_type());
	}

	TEST_F(ComputerPlayer_Test, ChooseSmartly)
	{
		ASSERT_EQ(3, p_Computer->choose_matches(4, false));
		ASSERT_EQ(2, p_Computer->choose_matches(3, false));
		ASSERT_EQ(1, p_Computer->choose_matches(2, false));
		ASSERT_EQ(1, p_Computer->choose_matches(1, false));
		ASSERT_EQ(3, p_Computer->choose_matches(8, false));
		ASSERT_EQ(2, p_Computer->choose_matches(7, false));
		ASSERT_EQ(1, p_Computer->choose_matches(6, false));
		ASSERT_EQ(1, p_Computer->choose_matches(5, false));
	}

	TEST_F(ComputerPlayer_Test, DetermineRandomness)
	{
		ASSERT_EQ(true, p_Computer->determine_randomness(cl_player::EASY));
		ASSERT_EQ(false, p_Computer->determine_randomness(cl_player::HARD));

		// Test medium difficulty: verify that 49-51 % of cases are random
		float num_of_tests = 10000.0;
		float num_of_randoms = 0.0;
		for (int i = 0; i < num_of_tests; ++i)
		{
			if (p_Computer->determine_randomness(cl_player::MEDIUM))
			{
				num_of_randoms += 1.0;
			}
		}
		ASSERT_NEAR(0.5, num_of_randoms / num_of_tests, 0.01);
	}

	// Test random choosing: verify that all number of matches have 32-34 % likelyhood
	TEST_F(ComputerPlayer_Test, ChooseRandomlyUnlimited)
	{
		float num_of_tests = 10000.0;
		float num_of_ones = 0.0;
		float num_of_twos = 0.0;
		float num_of_threes = 0.0;

		for (int i = 0; i < num_of_tests; ++i)
		{
			int number_of_matches = p_Computer->choose_matches(10, true);
			if (number_of_matches == 1)
			{
				num_of_ones += 1.0;
			}
			else if (number_of_matches == 2)
			{
				num_of_twos += 1.0;
			}
			else if (number_of_matches == 3)
			{
				num_of_threes += 1.0;
			}
		}

		ASSERT_NEAR(1.0 / 3.0, num_of_ones / num_of_tests, 0.01);
		ASSERT_NEAR(1.0 / 3.0, num_of_twos / num_of_tests, 0.01);
		ASSERT_NEAR(1.0 / 3.0, num_of_threes / num_of_tests, 0.01);
	}

	// Test random choosing when picking from a pile that has 2 matches: Verify that 
	// 1 match has 32-34 % likelyhood and two matches 66-68 % likelyhood
	TEST_F(ComputerPlayer_Test, ChooseRandomlyLimited)
	{
		float num_of_tests = 10000.0;
		float num_of_ones = 0.0;
		float num_of_twos = 0.0;

		for (int i = 0; i < num_of_tests; ++i)
		{
			int number_of_matches = p_Computer->choose_matches(2, true);
			if (number_of_matches == 1)
			{
				num_of_ones += 1.0;
			}
			else if (number_of_matches == 2)
			{
				num_of_twos += 1.0;
			}
		}

		ASSERT_NEAR(1.0 / 3.0, num_of_ones / num_of_tests, 0.01);
		ASSERT_NEAR(2.0 / 3.0, num_of_twos / num_of_tests, 0.01);
	}

	TEST_F(ComputerPlayer_Test, PlayTurn)
	{
		ASSERT_EQ(3, p_Computer->play_turn(4));
	}

}	//namespace