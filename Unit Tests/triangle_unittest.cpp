#include "gtest/gtest.h"
#include "triangle.h"

#include <vector>

// Equality operator so that ASSERT_EQ is able to compare two T_coordinates instances.
bool operator == (const T_coordinates& a, const T_coordinates& b)
{
	return (a.x == b.x && a.y == b.y);
}

namespace
{
	std::vector<int> NumberOfMatches = { 0, 1, 6, 7, 8, 9, 10 };
	std::vector<int> ExpectedNumberOfRows = { 0, 1, 3, 3, 3, 3, 4 };
	std::vector<std::vector<int>> ExpectedMatchesAtRows = { {0}, {1}, {1,2,3}, {1,2,4}, {1,3,4}, {2,3,4}, {1,2,3,4} };
	std::vector<T_coordinates> ExpectedGrids = { {0,0}, {1,1}, {5,3}, {7,3}, {7,3}, {7,3}, {7,4} };
	std::vector<std::vector<T_coordinates>> ExpectedCoordinates = 
	{
		{{0,0}},
		{{0,0}},
		{{2,0}, {1,1}, {3,1}, {0,2}, {2,2}, {4,2}},
		{{3,0}, {2,1}, {4,1}, {0,2}, {2,2}, {4,2}, {6,2}},
		{{3,0}, {1,1}, {3,1}, {5,1}, {0,2}, {2,2}, {4,2}, {6,2}},
		{{2,0}, {4,0}, {1,1}, {3,1}, {5,1}, {0,2}, {2,2}, {4,2}, {6,2}},
		{{3,0}, {2,1}, {4,1}, {1,2}, {3,2}, {5,2}, {0,3}, {2,3}, {4,3}, {6,3}}
	};

	TEST(TriangleTest, HelperFunctions)
	{
		for (unsigned int i = 0; i < NumberOfMatches.size(); ++i)
		{
			int number_of_rows = calculate_number_of_rows(NumberOfMatches[i]);
			ASSERT_EQ(ExpectedNumberOfRows[i], number_of_rows);
			ASSERT_EQ(ExpectedMatchesAtRows[i], calculate_matches_in_rows(NumberOfMatches[i], number_of_rows));
		}
	}

	TEST(TriangleTest, GetGridSizes)
	{
		cl_triangle* p_Triangle;
		T_coordinates grid_size;

		for (unsigned int i = 0; i < NumberOfMatches.size(); ++i)
		{
			p_Triangle = new cl_triangle(NumberOfMatches[i]);
			grid_size = p_Triangle->get_grid_size();
			ASSERT_EQ(ExpectedGrids[i], grid_size);
			delete p_Triangle;
		}
	}
	
	TEST(TriangleTest, GetCoordinates)
	{
		cl_triangle* p_Triangle;
		std::vector<T_coordinates> coordinates;

		for (unsigned int i = 0; i < NumberOfMatches.size(); ++i)
		{
			p_Triangle = new cl_triangle(NumberOfMatches[i]);
			coordinates = p_Triangle->get_match_coordinates();
			ASSERT_EQ(ExpectedCoordinates[i], p_Triangle->get_match_coordinates()) << "Failed on match index " << i;
			delete p_Triangle;
		}
	}
}	//namespace
