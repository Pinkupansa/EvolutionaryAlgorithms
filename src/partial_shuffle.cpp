#include "partial_shuffle.hpp"
void PartialShuffle::mutate(int *chromosome, int chromosomeSize)
{
    int i = generator.uniformInt(0, chromosomeSize - 1);
    int j = generator.uniformInt(0, chromosomeSize - 1);

    if (i > j)
    {
        int temp = i;
        i = j;
        j = temp;
    }

    // Shuffle the subarray
    for (int k = i; k < j; k++)
    {
        int l = generator.uniformInt(k, j);
        int temp = chromosome[k];
        chromosome[k] = chromosome[l];
        chromosome[l] = temp;
    }
}