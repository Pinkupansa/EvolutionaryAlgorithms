
#include <matplot/matplot.h>
#include "xoroshiro_generator.hpp"
#include <random>
#include <time.h>
void test_binomial()
{

    XoroshiroGenerator generator = XoroshiroGenerator();
    int n = 100;
    double p = 0.2;
    int trials = 1000000;
    int binomial[trials];
    clock_t start = clock();

    for (int i = 0; i < trials; i++)
    {
        binomial[i] = generator.binomial(n, p);
    }

    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time elapsed: " << elapsed << std::endl;

    int occurences[n];
    for (int i = 0; i < n; i++)
    {
        occurences[i] = 0;
    }
    for (int i = 0; i < trials; i++)
    {
        occurences[binomial[i]]++;
    }
    // plot
    std::vector<double> x(n);
    std::vector<double> y(n);
    for (int i = 0; i < n; i++)
    {
        x[i] = i;
        y[i] = occurences[i] / (0.0 + trials);
    }
    // set y range to [0,1]
    matplot::ylim({0, 1});
    matplot::plot(x, y);
    matplot::show();
}
int main(int argc, char **argv)
{
    srand(time(NULL));
    test_binomial();
    return 0;
}
