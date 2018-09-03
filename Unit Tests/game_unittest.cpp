#include "gtest/gtest.h"
#include "game.h"
#include "player.h"

#include "keyboard_buffer_mock.h"

#include <vector>

namespace
{
	class Game_Test : public testing::Test
	{
	protected:
        virtual void SetUp()
        {
            player_settings = { cl_game::TWO, {{"Tietsari 1", cl_player::COMPUTER, cl_player::HARD}, { "Tietsari 2", cl_player::COMPUTER, cl_player::HARD }} };
            pile_settings = { 2, cl_matchpile::NO };
		    p_Game = new cl_game(kb_buffer_mock, player_settings, pile_settings);
		}

		virtual void TearDown()
		{
			delete p_Game;
		}

        cl_game::T_player_settings player_settings;
        cl_matchpile::MatchPileSettings pile_settings;
        KeyboardBufferMock kb_buffer_mock = KeyboardBufferMock({keyboardbuffer::kOne});
	    cl_game* p_Game;
	};

	TEST_F(Game_Test, PlayGame)
	{
		ASSERT_EQ(0, p_Game->get_turn());
		ASSERT_EQ("Tietsari 1", p_Game->p_get_active_player()->get_player_name());
		p_Game->play_game();
		ASSERT_EQ(5, p_Game->get_turn());
		ASSERT_EQ("Tietsari 1", p_Game->p_get_active_player()->get_player_name());
	}
}	//namespace
