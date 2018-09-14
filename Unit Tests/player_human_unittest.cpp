#include "gtest/gtest.h"
#include "human_player.h"

#include "keyboard_buffer_mock.h"
#include "match_pile_mock.h"

namespace
{
	// Constants
	std::string PlayerName = "Ihminen";

	TEST(HumanPlayer_Test, Constructor)
	{
        KeyboardBufferMock kb_buffer_mock({ keyboardbuffer::kThree, keyboardbuffer::kTwo, keyboardbuffer::kOne });
        
        MatchPileMock match_pile = MatchPileMock(10);
        
        Player* p_Human = new HumanPlayer(kb_buffer_mock, PlayerName, &match_pile);
        ASSERT_EQ("Ihminen", p_Human->get_player_name());
	}

	TEST(HumanPlayer_Test, PlayTurnPicking3Matches)
	{
        KeyboardBufferMock kb_buffer_mock({ keyboardbuffer::kThree, keyboardbuffer::kTwo, keyboardbuffer::kOne });

        MatchPileMock match_pile = MatchPileMock(3);

        Player* p_Human = new HumanPlayer(kb_buffer_mock, PlayerName, &match_pile);
        p_Human->play_turn();
        ASSERT_EQ(0, match_pile.get_remaining_matches());
	}
	
	TEST(HumanPlayer_Test, PlayTurnPicking2Matches)
	{
        KeyboardBufferMock kb_buffer_mock({ keyboardbuffer::kThree, keyboardbuffer::kTwo, keyboardbuffer::kOne });

        MatchPileMock match_pile = MatchPileMock(2);

        Player* p_Human = new HumanPlayer(kb_buffer_mock, PlayerName, &match_pile);
        p_Human->play_turn();
        ASSERT_EQ(0, match_pile.get_remaining_matches());
	}

	TEST(HumanPlayer_Test, PlayTurnPicking1Match)
	{
        KeyboardBufferMock kb_buffer_mock({ keyboardbuffer::kThree, keyboardbuffer::kTwo, keyboardbuffer::kOne });

        MatchPileMock match_pile = MatchPileMock(1);

        Player* p_Human = new HumanPlayer(kb_buffer_mock, PlayerName, &match_pile);
        p_Human->play_turn();
        ASSERT_EQ(0, match_pile.get_remaining_matches());
	}

}	//namespace