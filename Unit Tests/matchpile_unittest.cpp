#include "gtest/gtest.h"
#include "matchpile.h"

#include <string>

namespace
{
	// Constants
	int MatchMultiplier = 3;

	class MatchPile_Test : public testing::Test
	{
	protected:
		virtual void SetUp()
		{
            pile_settings = { 3, cl_matchpile::NO };
		    p_MatchPile = new cl_matchpile(pile_settings);
		}

		virtual void TearDown()
		{
			delete p_MatchPile;
		}

		cl_matchpile* p_MatchPile;
        cl_matchpile::MatchPileSettings pile_settings;
	};

	// Testing constructor, match multiplier 3
	TEST(MatchPile_ConstructorTest, Multiplier3)
	{
		cl_matchpile MyPile({ 3, cl_matchpile::NO });
		ASSERT_EQ(13, MyPile.get_remaining_matches());
	}

	// Testing constructor, match multiplier 4
	TEST(MatchPile_ConstructorTest, Multiplier4)
	{
		cl_matchpile MyPile({ 4, cl_matchpile::NO });
		ASSERT_EQ(17, MyPile.get_remaining_matches());
	}

	// Testing removing match
	TEST_F(MatchPile_Test, RemoveMatch)
	{
		// Verify right number of matches after initialization
		ASSERT_EQ(13, p_MatchPile->get_remaining_matches());

		// Remove a match
		p_MatchPile->remove_matches(1);
		ASSERT_EQ(12, p_MatchPile->get_remaining_matches());

		// Remove rest of the mathes
		p_MatchPile->remove_matches(12);
		ASSERT_EQ(0, p_MatchPile->get_remaining_matches());

		// Ensure that number of matches cannot go negative
		p_MatchPile->remove_matches(1);
		ASSERT_EQ(0, p_MatchPile->get_remaining_matches());
	}

	// Test printing matches
	TEST_F(MatchPile_Test, PrintMatches)
	{
		std::string PileExpected = "    I    \n  I I I  \n I I I I \nI I I I I\n\n";
		ASSERT_EQ(PileExpected, p_MatchPile->print_matches());

		// Remove some matches and verify printing also after that
		p_MatchPile->remove_matches(5);
		PileExpected = "         \n         \n   I I I \nI I I I I\n\n";
		ASSERT_EQ(PileExpected, p_MatchPile->print_matches());
	}
}	//namespace