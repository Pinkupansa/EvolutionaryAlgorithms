#include "standard_bit_mutation.hpp"

StandardBitMutation::StandardBitMutation(double mutationRate)
{
    this->mutationRate = mutationRate;
    this->generator = XoroshiroGenerator();
}

void StandardBitMutation::mutate(int *chromosome, int chromosomeSize)
{
    int mutationCount = generator.binomial(chromosomeSize, mutationRate);

    for (int i = 0; i < mutationCount; i++)
    {
        int mutationIndex = generator.uniformInt(0, chromosomeSize - 1);
        chromosome[mutationIndex] = 1 - chromosome[mutationIndex];
    }
}