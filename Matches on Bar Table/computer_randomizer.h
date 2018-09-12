#ifndef COMPUTER_RANDOMIZER_H
#define COMPUTER_RANDOMIZER_H

#include <random>

class ComputerRandomizer
{
public:
    ComputerRandomizer(unsigned seed) : generator_(seed), pick_randomly_(0, 1), random_matches_(1, 3) {}

    bool randomness()
    {
        return pick_randomly_(generator_) == 1;
    }

    int match_count()
    {
        return random_matches_(generator_);
    }

private:
    std::default_random_engine generator_;
    std::uniform_int_distribution<int> pick_randomly_;
    std::uniform_int_distribution<int> random_matches_;
};

#endif // I_COMPUTER_RANDOMIZER_H
