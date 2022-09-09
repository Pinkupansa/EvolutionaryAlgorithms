#include <iostream>

#include "benchmark_functions.hpp"
#include "hill_climber.hpp"
#include "evolution_interface.hpp"
// Default main
int main(int argc, char **argv) {
    int chromosomeSize = 1000;
    double(*jumpFunction)(int*, int) = [](int* chromosome, int chromosomeSize) {
        return jump(chromosome, chromosomeSize, 3);
    };

    HillClimber HillClimber(chromosomeSize, 3);
    EvolutionInterface EvolutionInterface(&HillClimber, 100000, &oneMax);
    EvolutionInterface.run();
}