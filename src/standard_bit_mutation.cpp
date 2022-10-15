#include "standard_bit_mutation.hpp"
#include <random>

StandardBitMutation::StandardBitMutation(double mutationRate)
{
    this->mutationRate = mutationRate;
}

void StandardBitMutation::mutate(int *chromosome, int chromosomeSize)
{
    
    for (int i = 0; i < chromosomeSize; i++)
    {
        if (rand() % 100 < mutationRate * 100)
        {
            chromosome[i] = !chromosome[i];
        }
    }
}