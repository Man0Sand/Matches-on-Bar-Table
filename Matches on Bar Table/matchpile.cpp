#include <string>
#include <vector>

#include "matchpile.h"

//----------------------------------------------------------------------------------------------------------------------------
// Do this better in the future...
//----------------------------------------------------------------------------------------------------------------------------

#include <time.h>
#include <stdlib.h>

static void swap_int(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

static inline int rand_int_hi_lo(int upper, int lower)
{
	return((rand() % (upper - lower + 1)) + lower);
}

static int rand_int(int a, int b)
{
	if (b > a) swap_int(&a, &b);
	return rand_int_hi_lo(a, b);
}
//----------------------------------------------------------------------------------------------------------------------------

cl_matchpile::cl_matchpile(const MatchPileSettings& match_pile_settings):
m_matches(1 + match_pile_settings.match_multiplier * 4),
m_it_matches(m_matches.begin())
{
	cl_triangle grid_creator(m_matches.size());
	initialize_grid(grid_creator.get_grid_size(), &m_match_grid);
	map_grid(grid_creator.get_match_coordinates(), m_matches, &m_match_grid, match_pile_settings.pick_matches_randomly);
}

void initialize_grid(const T_coordinates& grid_size, T_match_grid* p_match_grid)
{
	std::vector<cl_match*> null_vector_row(grid_size.x, 0);
	for (int row = 0; row < grid_size.y; ++row)
	{
		p_match_grid->push_back(null_vector_row);
	}
}

bool find_int(std::vector<int> nums, int searched_num)
{
	for (int num : nums)
	{
		if (num == searched_num)
		{
			return true;
		}
	}

	return false;
}

void map_grid(const std::vector<T_coordinates>& match_coordinates, std::vector<cl_match>& matches, T_match_grid* p_match_grid, bool map_randomly)
{
	unsigned int number_of_matches = matches.size();
	std::vector<int> mapping_indexes;

	if (map_randomly)
	{
		srand(time(0));
		int random_number;

		while (mapping_indexes.size() != number_of_matches)
		{
			random_number = rand_int(0, number_of_matches - 1);
			if (!find_int(mapping_indexes, random_number))
			{
				mapping_indexes.push_back(random_number);
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < number_of_matches; ++i)
		{
			mapping_indexes.push_back(i);
		}
	}

	for (unsigned int i = 0; i < number_of_matches; ++i)
	{
		(*p_match_grid)[match_coordinates[i].y][match_coordinates[i].x] = &matches[mapping_indexes[i]];
	}
}

int cl_matchpile::get_remaining_matches(void)
{
	int number_of_matches = 0;
	for (cl_match match : m_matches)
	{
		if (!match.is_removed())
		{
			++number_of_matches;
		}
	}

	return number_of_matches;
}

void cl_matchpile::remove_matches(int number_of_matches)
{
    if (number_of_matches <= get_remaining_matches())
    {
		for (int i = 0; i < number_of_matches; ++i)
		{
			m_it_matches->remove();
			if (m_it_matches != m_matches.end() - 1)
			{
				++m_it_matches;
			}
		}
    }
}

std::string cl_matchpile::print_matches()
{
	std::string match_pile = "";
	std::string element_content = "";
	for (unsigned int i = 0; i < m_match_grid.size(); ++i)
	{
		for (unsigned int j = 0; j < m_match_grid[i].size(); ++j)
		{
			element_content = " ";
			if (m_match_grid[i][j])
			{
				if (!m_match_grid[i][j]->is_removed())
				{
					element_content = "I";
				}
			}
			match_pile += element_content;
		}
		match_pile += "\n";
	}
	match_pile += "\n";
	
	return match_pile;
}
