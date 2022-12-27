#include "ga_visualizer.hpp"

GAVisualizer::GAVisualizer()
{
    matplot::figure();
    matplot::hold(matplot::on);

}

void GAVisualizer::refresh(double newBestFitness)
{
    bestFitnesses.push_back(newBestFitness);
    matplot::plot(bestFitnesses);
    //matplot::pause(0.001);
}

