#include "Random.h"
#include "Define.h"

using namespace std;
using dist_type = std::uniform_int_distribution<>;

Random::Random()
{
    // Initialize the generator with Hardware Random Seed
    random_device rnd;
    _mt.seed(rnd());

    // Reset the state of normal_distribution.
    _dist.reset();
    
    // Initialize the range from Define::MIN to Define::MAX.
    dist_type::param_type param(Define::MIN, Define::MAX);
    _dist.param(param);
}

Random::Random(int N)
{
    // Initialize the generator with Hardware Random Seed
    random_device rnd;
    _mt.seed(rnd());

    // Reset the state of normal_distribution.
    _dist.reset();
    
    // Initialize the range from 1 to N - 1.
    dist_type::param_type param(1, N - 1);
    _dist.param(param);
}

Random::Random(int min, int max)
{
    // Initialize the generator with Hardware Random Seed
    random_device rnd;
    _mt.seed(rnd());

    // Reset the state of normal_distribution.
    _dist.reset();
    
    // Initialize the range from min to max.
    dist_type::param_type param(min, max);
    _dist.param(param);
}

void Random::reset()
{
    _dist.reset();
}

void Random::range(int min, int max)
{
    // Set the range from min to max.
    _dist.param(dist_type::param_type(min, max));
}

void Random::seed(unsigned int seed)
{
    // Set the seed
    _mt.seed(seed);
}