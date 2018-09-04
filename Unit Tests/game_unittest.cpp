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
            p_match_pile = new cl_matchpile(pile_settings);
            for (int i = 0; i < player_settings.number_of_players; ++i)
            {
                p_players.push_back(cl_player::create(kb_buffer_mock, player_settings.player_config[i], p_match_pile));
            }
            p_Game = new cl_game(kb_buffer_mock, p_match_pile, p_players);
		}

		virtual void TearDown()
		{
            delete p_Game;
            for (cl_player* p_player : p_players)
            {
                //delete p_player;    // wonder why this causes SEH exception...
            }
            delete p_match_pile;
		}

        cl_game::T_player_settings player_settings = { cl_game::TWO,{ { "Tietsari 1", cl_player::COMPUTER, cl_player::HARD },{ "Tietsari 2", cl_player::COMPUTER, cl_player::HARD } } };
        cl_matchpile::MatchPileSettings pile_settings = { 2, cl_matchpile::NO };

        KeyboardBufferMock kb_buffer_mock = KeyboardBufferMock({keyboardbuffer::kOne});
        cl_matchpile* p_match_pile;
        std::vector<cl_player*> p_players;
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
