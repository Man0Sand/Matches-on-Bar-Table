#include "gtest/gtest.h"
#include "match.h"

namespace
{
	TEST(MatchTest, Constructor)
	{
		cl_match match;
		ASSERT_EQ(false, match.is_removed());
	}

	TEST(MatchTest, RemoveMatch)
	{
		cl_match match;
		match.remove();
		ASSERT_EQ(true, match.is_removed());
	}
}