#pragma once
#include "Define.h"
#include <random>

/// @brief Random Number Generator
/// @details Random numbers are generated based on the uniform distribution using a pseudo-random number generator based on the Mersenne Twister method.
/// @note Set the range with range().
/// @note Set the seed with seed().
class Random final
{
private:
    std::mt19937 _mt;
    std::uniform_int_distribution<> _dist;

public:
    /// @brief Constructor
    /// @note Initialize the range from 1 to N - 1.
    /// @note Initialize the seed with hardware random number.
    Random();

    /// @brief Constructor
    /// @param N the upper bound
    /// @note Initialize the range from 1 to N - 1.
    /// @note Initialize the seed with hardware random number.
    Random(int N);

    /// @brief Constructor
    /// @param min the lower bound
    /// @param max the upper bound
    /// @note Initialize the range from min to max.
    /// @note Initialize the seed with hardware random number.
    Random(int min, int max);

    ~Random() = default;

    /// @brief Reset the param
    /// @details Reset the parameters.
    void reset();

    /// @brief Return random integer
    /// @details Return random integer such that min() <= N <= max()
    int operator()() { return _dist(_mt); };

    /// @brief Set the parameters
    /// @details Set the range of the values that can be generated.
    /// @param min The lower bound
    /// @param max The upper bound
    void range(int min, int max);

    /// @brief Set the seed
    /// @details Set the seed for the random number generator
    /// @param seed Seed for the random number generator
    void seed(unsigned int seed);

    /// @brief Get the upper bound
    /// @details Get the upper bound value that can be generated.
    /// @return The upper bound value
    int max() { return _dist.max(); };

    /// @brief Get the lower bound
    /// @details Get the lower bound value that can be generated.
    /// @return The lower bound value
    int min() { return _dist.min(); };
};