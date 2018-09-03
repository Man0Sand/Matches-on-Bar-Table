#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

struct T_coordinates
{
	int x;
	int y;
};

class cl_triangle
{
public:
	cl_triangle(int number_of_matches);
	T_coordinates get_grid_size();
	std::vector<T_coordinates> get_match_coordinates();
private:
	int m_number_of_matches;
	int m_number_of_rows;
	std::vector<int> m_matches_at_rows;
	int m_matches_at_last_row;
	void initialize(int number_of_matches);
};

int calculate_number_of_rows(int number_of_matches);
std::vector<int> calculate_matches_in_rows(int number_of_matches, int number_of_rows);

#endif // TRIANGLE_H