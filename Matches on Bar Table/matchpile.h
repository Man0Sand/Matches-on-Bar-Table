#ifndef MATCHPILE_H
#define MATCHPILE_H

#include <string>
#include <vector>

#include "match.h"
#include "triangle.h"

typedef std::vector<std::vector<cl_match*>> T_match_grid;

class cl_matchpile
{
public:
    enum e_pick_matches_randomly
    {
        NO = 0,
        YES
    };
    struct MatchPileSettings
    {
        int match_multiplier;
        e_pick_matches_randomly pick_matches_randomly;
    };
    cl_matchpile(const MatchPileSettings& match_pile_settings);
    int get_remaining_matches(void);
    std::string print_matches(void);
    void remove_matches(int number_of_matches);
private:
	std::vector<cl_match> m_matches;
	std::vector<cl_match>::iterator m_it_matches;
	T_match_grid m_match_grid;
};

void initialize_grid(const T_coordinates& grid_size, T_match_grid* p_match_grid);
void map_grid(const std::vector<T_coordinates>& match_coordinates, std::vector<cl_match>& matches, T_match_grid* p_match_grid, bool map_randomly);

#endif // MATCHPILE_H
