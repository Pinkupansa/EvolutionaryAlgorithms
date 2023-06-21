#include "ga_visualizer.hpp"

GAVisualizer::GAVisualizer()
{
    // matplot::figure();
    // matplot::hold(matplot::on);
}

void GAVisualizer::refresh(double newBestFitness, double newWorstFitness)
{
    bestFitnesses.push_back(newBestFitness);
    matplot::plot(bestFitnesses);
    // matplot::pause(0.001);
    worstFitnesses.push_back(newWorstFitness);
    matplot::plot(worstFitnesses);
}

void GAVisualizer::displayLog(EALog log)
{
    matplot::figure();
    matplot::hold(matplot::on);
    matplot::plot(log.bestFitnesses);
    matplot::plot(log.worstFitnesses);
    matplot::title("Fitnesses");
    matplot::xlabel("Generation");
    matplot::ylabel("Fitness");
    matplot::legend({"Best", "Worst"});
    matplot::show();
}