#include "standard_bit_mutation.hpp"

StandardBitMutation::StandardBitMutation(double mutationRate)
{
    this->mutationRate = mutationRate;
    this->urng = std::default_random_engine();
}

void StandardBitMutation::mutate(int *chromosome, int chromosomeSize)
{
    // sample a binomial distribution with n = chromosomeSize and p = mutationRate
    std::binomial_distribution<int> distribution(chromosomeSize, mutationRate);
    int m = distribution(urng);
    // sample m random indices
    std::uniform_int_distribution<int> indexDistribution(0, chromosomeSize - 1);
    for (int i = 0; i < m; i++)
    {
        int index = indexDistribution(urng);
        chromosome[index] = 1 - chromosome[index];
    }
}