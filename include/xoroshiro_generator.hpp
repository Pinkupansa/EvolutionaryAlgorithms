#ifndef XOROSHIRO_HPP
#define XOROSHIRO_HPP
/*  Written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <stdint.h>

/* This is xoshiro256++ 1.0, one of our all-purpose, rock-solid generators.
   It has excellent (sub-ns) speed, a state (256 bits) that is large
   enough for any parallel application, and it passes all tests we are
   aware of.

   For generating just floating-point numbers, xoshiro256+ is even faster.

   The state must be seeded so that it is not everywhere zero. If you have
   a 64-bit seed, we suggest to seed a splitmix64 generator and use its
   output to fill s. */

class XoroshiroGenerator
{
public:
    XoroshiroGenerator();
    int uniformInt(int min, int max);
    double uniformDouble(double min, double max);
    double normal(double mean, double stddev);
    double poisson(double lambda);
    int binomial(int n, double p);

private:
    /* This is the jump function for the generator. It is equivalent
    to 2^128 calls to next(); it can be used to generate 2^128
    non-overlapping subsequences for parallel computations. */

    void jump(void);

    /* This is the long-jump function for the generator. It is equivalent to
    2^192 calls to next(); it can be used to generate 2^64 starting points,
    from each of which jump() will generate 2^64 non-overlapping
    subsequences for parallel distributed computations. */

    void long_jump(void);
    uint64_t next(void);
    uint64_t rotl(const uint64_t x, int k);

    uint64_t s[4];
};

#endif