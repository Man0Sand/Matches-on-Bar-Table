#include "gtest/gtest.h"
#include "player.h"

#include "keyboard_buffer_mock.h"
#include "matchpile.h"

namespace
{
	// Constants
	std::string PlayerName = "Ihminen";

	TEST(HumanPlayer_Test, Constructor)
	{
        KeyboardBufferMock kb_buffer_mock({ keyboardbuffer::kThree, keyboardbuffer::kTwo, keyboardbuffer::kOne });
        
        cl_matchpile::MatchPileSettings pile_settings = { 2, cl_matchpile::NO };
        cl_matchpile match_pile = cl_matchpile(pile_settings);
        
        cl_player_human* p_Human = new cl_player_human(kb_buffer_mock, PlayerName, &match_pile);
        ASSERT_EQ("Ihminen", p_Human->get_player_name());
	}

	TEST(HumanPlayer_Test, PlayTurnPicking3Matches)
	{
        KeyboardBufferMock kb_buffer_mock({ keyboardbuffer::kThree, keyboardbuffer::kTwo, keyboardbuffer::kOne });

        cl_matchpile::MatchPileSettings pile_settings = { 2, cl_matchpile::NO };
        cl_matchpile match_pile = cl_matchpile(pile_settings);

        cl_player_human* p_Human = new cl_player_human(kb_buffer_mock, PlayerName, &match_pile);
        p_Human->play_turn();
        ASSERT_EQ(6, match_pile.get_remaining_matches());
	}
	
    // Mock the pile and add an assertation in the end of test!
	TEST(HumanPlayer_Test, DISABLED_PlayTurnPicking2Matches)
	{
        KeyboardBufferMock kb_buffer_mock({ keyboardbuffer::kThree, keyboardbuffer::kTwo, keyboardbuffer::kOne });

        cl_matchpile::MatchPileSettings pile_settings = { 2, cl_matchpile::NO };
        cl_matchpile match_pile = cl_matchpile(pile_settings);

        cl_player_human* p_Human = new cl_player_human(kb_buffer_mock, PlayerName, &match_pile);
	}

    // Mock the pile and add an assertation in the end of test!
	TEST(HumanPlayer_Test, DISABLED_PlayTurnPicking1Match)
	{
        KeyboardBufferMock kb_buffer_mock({ keyboardbuffer::kThree, keyboardbuffer::kTwo, keyboardbuffer::kOne });

        cl_matchpile::MatchPileSettings pile_settings = { 2, cl_matchpile::NO };
        cl_matchpile match_pile = cl_matchpile(pile_settings);

        cl_player_human* p_Human = new cl_player_human(kb_buffer_mock, PlayerName, &match_pile);
	}

}	//namespace