#ifndef GA_VISUALIZER_HPP
#define GA_VISUALIZER_HPP

#include <matplot/matplot.h>
#include <vector>
#include "ea_log.hpp"

class GAVisualizer
{
public:
    GAVisualizer();
    void refresh(double newBestFitness, double newWorstFitness);
    void displayLog(EALog log);

private:
    std::vector<double> bestFitnesses;
    std::vector<double> worstFitnesses;
};
#endif