#include "xoroshiro_generator.hpp"

/*  Written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <stdint.h>
#include <random>

/* This is xoshiro256++ 1.0, one of our all-purpose, rock-solid generators.
   It has excellent (sub-ns) speed, a state (256 bits) that is large
   enough for any parallel application, and it passes all tests we are
   aware of.

   For generating just floating-point numbers, xoshiro256+ is even faster.

   The state must be seeded so that it is not everywhere zero. If you have
   a 64-bit seed, we suggest to seed a splitmix64 generator and use its
   output to fill s. */

static const uint64_t JUMP[] = {0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c};
static const uint64_t LONG_JUMP[] = {0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635};

inline uint64_t XoroshiroGenerator::rotl(const uint64_t x, int k)
{
    return (x << k) | (x >> (64 - k));
}

uint64_t XoroshiroGenerator::next(void)
{
    const uint64_t result = rotl(s[0] + s[3], 23) + s[0];

    const uint64_t t = s[1] << 17;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= t;

    s[3] = rotl(s[3], 45);

    return result;
}

/* This is the jump function for the generator. It is equivalent
   to 2^128 calls to next(); it can be used to generate 2^128
   non-overlapping subsequences for parallel computations. */

void XoroshiroGenerator::jump(void)
{

    uint64_t s0 = 0;
    uint64_t s1 = 0;
    uint64_t s2 = 0;
    uint64_t s3 = 0;
    for (int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
        for (int b = 0; b < 64; b++)
        {
            if (JUMP[i] & UINT64_C(1) << b)
            {
                s0 ^= s[0];
                s1 ^= s[1];
                s2 ^= s[2];
                s3 ^= s[3];
            }
            next();
        }

    s[0] = s0;
    s[1] = s1;
    s[2] = s2;
    s[3] = s3;
}

/* This is the long-jump function for the generator. It is equivalent to
   2^192 calls to next(); it can be used to generate 2^64 starting points,
   from each of which jump() will generate 2^64 non-overlapping
   subsequences for parallel distributed computations. */

void XoroshiroGenerator::long_jump(void)
{

    uint64_t s0 = 0;
    uint64_t s1 = 0;
    uint64_t s2 = 0;
    uint64_t s3 = 0;
    for (int i = 0; i < sizeof LONG_JUMP / sizeof *LONG_JUMP; i++)
        for (int b = 0; b < 64; b++)
        {
            if (LONG_JUMP[i] & UINT64_C(1) << b)
            {
                s0 ^= s[0];
                s1 ^= s[1];
                s2 ^= s[2];
                s3 ^= s[3];
            }
            next();
        }

    s[0] = s0;
    s[1] = s1;
    s[2] = s2;
    s[3] = s3;
}

int XoroshiroGenerator::uniformInt(int min, int max)
{
    return min + (next() % (max - min + 1));
}

int XoroshiroGenerator::binomial(int n, double p)
{
    if (p > 0.5)
    {
        return n - binomial(n, 1 - p);
    }

    if (n < 20)
    {
        // count number of successes
        int successes = 0;
        for (int i = 0; i < n; i++)
        {
            if (uniformDouble(0, 1) < p)
            {
                successes++;
            }
        }
        return successes;
    }

    if (n * p < 20)
    {
        // use poisson approximation
        return poisson(n * p);
    }

    // use normal approximation
    double mean = n * p;
    double stddev = sqrt(n * p * (1 - p));
    return normal(mean, stddev);
}

double XoroshiroGenerator::uniformDouble(double min, double max)
{
    return min + (next() / (double)UINT64_MAX) * (max - min);
}

double XoroshiroGenerator::normal(double mean, double stddev)
{
    double u1 = uniformDouble(0, 1);
    double u2 = uniformDouble(0, 1);
    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    return mean + stddev * z0;
}

double XoroshiroGenerator::poisson(double lambda)
{
    double L = std::exp(-lambda);
    double p = 1;
    int k = 0;

    while (p > L)
    {
        k++;
        p *= uniformDouble(0, 1);
    }

    return k - 1;
}

XoroshiroGenerator::XoroshiroGenerator()
{

    s[0] = rand();
    s[1] = rand();
    s[2] = rand();
    s[3] = rand();
}
