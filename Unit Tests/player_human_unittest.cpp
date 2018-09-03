#include "gtest/gtest.h"
#include "player.h"

#include "keyboard_buffer_mock.h"

namespace
{
	// Constants
	std::string PlayerName = "Ihminen";

	TEST(HumanPlayer_Test, Constructor)
	{
        KeyboardBufferMock kb_buffer_mock({ keyboardbuffer::kThree, keyboardbuffer::kTwo, keyboardbuffer::kOne });
        cl_player_human* p_Human = new cl_player_human(kb_buffer_mock, PlayerName);
        ASSERT_EQ("Ihminen", p_Human->get_player_name());
	}

	TEST(HumanPlayer_Test, PlayTurnPicking3Matches)
	{
        KeyboardBufferMock kb_buffer_mock({ keyboardbuffer::kThree, keyboardbuffer::kTwo, keyboardbuffer::kOne });
        cl_player_human* p_Human = new cl_player_human(kb_buffer_mock, PlayerName);
        ASSERT_EQ(3, p_Human->play_turn(3));
	}
	
	TEST(HumanPlayer_Test, PlayTurnPicking2Matches)
	{
        KeyboardBufferMock kb_buffer_mock({ keyboardbuffer::kThree, keyboardbuffer::kTwo, keyboardbuffer::kOne });
        cl_player_human* p_Human = new cl_player_human(kb_buffer_mock, PlayerName);
        ASSERT_EQ(2, p_Human->play_turn(2));
	}

	TEST(HumanPlayer_Test, PlayTurnPicking1Match)
	{
        KeyboardBufferMock kb_buffer_mock({ keyboardbuffer::kThree, keyboardbuffer::kTwo, keyboardbuffer::kOne });
        cl_player_human* p_Human = new cl_player_human(kb_buffer_mock, PlayerName);
        ASSERT_EQ(1, p_Human->play_turn(1));
	}

}	//namespace