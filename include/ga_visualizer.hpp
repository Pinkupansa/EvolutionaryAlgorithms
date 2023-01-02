#ifndef GA_VISUALIZER_HPP
#define GA_VISUALIZER_HPP

#include <matplot/matplot.h>
#include <vector>

class GAVisualizer
{
public:
    GAVisualizer();
    void refresh(double newBestFitness, double newWorstFitness);

private:
    std::vector<double> bestFitnesses;
    std::vector<double> worstFitnesses;
};
#endif