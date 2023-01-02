#include "custom_segment_crossover.hpp"

#include <random>

CustomSegmentCrossover::CustomSegmentCrossover(int *segmentSizes, int segmentCount)
{
    this->segmentSizes = segmentSizes;
    this->segmentCount = segmentCount;
}

void CustomSegmentCrossover::crossover(ParentSelection *selection, int chromosomeSize, int **population, int *outOffspring)
{
    int current = 0;
    for (int i = 0; i < segmentCount; i++)
    {
        for (int j = 0; j < segmentSizes[i]; j++)
        {
            outOffspring[current] = population[selection->getParentsIndices()[i % selection->getNumberOfParents()]][current];
            current++;
        }
    }
}