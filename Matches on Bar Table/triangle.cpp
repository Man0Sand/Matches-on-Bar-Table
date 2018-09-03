#include "triangle.h"

cl_triangle::cl_triangle(int number_of_matches):
	m_number_of_matches(number_of_matches),
	m_number_of_rows(0),
	m_matches_at_rows(0),
	m_matches_at_last_row(0)
	{
		initialize(m_number_of_matches);
	}

void cl_triangle::initialize(int number_of_matches)
{
	if (!number_of_matches)
	{
		return;
	}

	m_number_of_rows = calculate_number_of_rows(number_of_matches);
	m_matches_at_rows = calculate_matches_in_rows(number_of_matches, m_number_of_rows);
	m_matches_at_last_row = m_matches_at_rows[m_matches_at_rows.size() - 1];
}

int calculate_number_of_rows(int number_of_matches)
{
	int number_of_rows = 0;
	
	// Number of matches in an equilateral triangle is x*(x+1)/2, where x is number of rows.
	while (((number_of_rows + 1)*(number_of_rows + 2) / 2) <= number_of_matches)
	{
		++number_of_rows;
	}

	// This could be also used, but static casting is nasty...
	//number_of_rows = static_cast<int>((sqrt(1 + 8 * number_of_matches) - 1) / 2);

	return number_of_rows;
}

std::vector<int> calculate_matches_in_rows(int number_of_matches, int number_of_rows)
{
	if (!number_of_matches)
	{
		return { 0 };
	}

	int number_of_extra_matches = number_of_matches - number_of_rows * (number_of_rows + 1) / 2;
	int number_of_rows_without_extra_match = number_of_rows - number_of_extra_matches;

	std::vector<int> matches_at_rows(number_of_rows);
	for (int i = 0; i < number_of_rows; i++)
	{
		if (i < number_of_rows_without_extra_match)
		{
			matches_at_rows[i] = i + 1;
		}
		else
		{
			matches_at_rows[i] = i + 2;
		}
	}

	return matches_at_rows;
}

T_coordinates cl_triangle::get_grid_size()
{
	if (!m_number_of_matches)
	{
		return { 0,0 };
	}
	
	T_coordinates grid_size = { 0,0 };
	grid_size.x = 2 * m_matches_at_last_row - 1;
	grid_size.y = m_number_of_rows;

	return grid_size;
}

std::vector<T_coordinates> cl_triangle::get_match_coordinates()
{
	if (!m_number_of_matches)
	{
		return { {0,0} };
	}
	
	std::vector<T_coordinates> match_coordinates(m_number_of_matches);

	int matches_at_row = 0;
	int match_idx = 0;

	for (int row = 0; row < m_number_of_rows; ++row)
	{
		matches_at_row = m_matches_at_rows[row];
		for (int column = 0; column < matches_at_row; ++column)
		{
			match_coordinates[match_idx].y = row;
			match_coordinates[match_idx].x = m_matches_at_last_row - matches_at_row + 2*column;
			++match_idx;
		}
	}

	return match_coordinates;
}
