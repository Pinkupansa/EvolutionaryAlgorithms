#ifndef GA_VISUALIZER_HPP
#define GA_VISUALIZER_HPP

#include <matplot/matplot.h>
#include <vector>

class GAVisualizer
{
public:
    GAVisualizer();
    void refresh(double newBestFitness);
private:
    std::vector<double> bestFitnesses;
};
#endif