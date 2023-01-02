#include "ga_visualizer.hpp"

GAVisualizer::GAVisualizer()
{
    matplot::figure();
    matplot::hold(matplot::on);
}

void GAVisualizer::refresh(double newBestFitness, double newWorstFitness)
{
    bestFitnesses.push_back(newBestFitness);
    matplot::plot(bestFitnesses);
    // matplot::pause(0.001);
    worstFitnesses.push_back(newWorstFitness);
}
