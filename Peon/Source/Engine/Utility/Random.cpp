#include "PCH.hpp"
#include "Random.hpp"

namespace grim
{

namespace utility
{

/*
    Generate a random double between min and max.
*/
double Random::Generate(double min, double max)
{
    std::random_device rand;
    std::mt19937 mt(rand());
    std::uniform_real_distribution<double> dist(min, max);

    return dist(mt);
}

}

}