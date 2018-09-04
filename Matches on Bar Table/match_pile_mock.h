#ifndef MATCH_PILE_MOCK_H
#define MATCH_PILE_MOCK_H

#include "I_match_pile.h"

class MatchPileMock : public I_MatchPile
{
public:
    MatchPileMock(int match_count) : number_of_matches_(match_count) {}
    
    int get_remaining_matches()
    {
        return number_of_matches_;
    }
    
    std::string print_matches()
    {
        return " ";
    }
    
    void remove_matches(int match_count)
    {
        number_of_matches_ -= match_count;
    }

private:
    int number_of_matches_;
};

#endif // MATCH_PILE_MOCK_H
