#ifndef I_MATCH_PILE_H
#define I_MATCH_PILE_H

#include <string>

class I_MatchPile
{
public:
    virtual int get_remaining_matches() = 0;
    virtual std::string print_matches() = 0;
    virtual void remove_matches(int match_count) = 0;
    virtual ~I_MatchPile() = default;
};

#endif // I_MATCH_PILE_H
