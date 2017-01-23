#include <iostream>
#include <iomanip>
#include "StepsInPrimes.hpp"

typedef std::size_t size_t;

void StepInPrimes::calculate_sieve(size_t N)
{
  size_t const n = sieve.size();
  if (N < n)
  {
    return;
  }
  if (N > std::numeric_limits<size_t>::max())
  {
    throw std::out_of_range("Maximum size of Sieve of Eratosthenes exceeded");
  }
  sieve.resize(static_cast<size_t>(N), true);
  // std::cout << "n==" << n << std::endl;
  // std::cout << "N==" << N << std::endl;
  for (size_t j = 0; j < N; ++j)
  {
    if (!sieve[j])
      continue;

    // std::cout << std::endl << "j==" << j+2 << std::endl;
    auto w = 0;

    for (auto k = (j + 2) * (j + 2) - 2; k < N; k += j + 2)
    {
      if (k < n)
        continue;

      sieve[k] = false;
      // std::cout << std::setw(5) << (k + 2) << ", ";
      if (++w > 9)
      {
        // std::cout << std::endl;
        w = 0;
      }
    }
  }
  if (N > n)
  {
    // std::cout << std::endl;
  }
}

bool StepInPrimes::is_prime(long long p)
{
  return p > 0 && (1 == p || 2 == p || (calculate_sieve(p - 1), sieve[p - 2]));
}

// if there are no such primes return {0, 0}
StepInPrimes::ll_pair StepInPrimes::step(int g, long long m, long long n)
{
  if (n > std::numeric_limits<long long>::max())
  {
    // and probably considerably less than that,
    // but who knows how big your computer might be?
    throw std::out_of_range("Cannot examine primes greater than "
      "std::numeric_limits<long long>::max()");
  }
  // Find first prime >= m
  auto const G = static_cast<size_t>(g);
  auto const M = static_cast<size_t>(m);
  auto const N = static_cast<size_t>(n);
  calculate_sieve(N);
  for (auto first = M; first <= N; ++first)
  {
    if (!is_prime(first))
    {
      //std::cout << "first==" << first << " not prime" << std::endl;
      continue;
    }
    //std::cout << "first==" << first << std::endl;
    auto next = first + G;
    // Find the prime candidate one step away.
    if (!is_prime(next))
    {
      continue;
    }
    return ll_pair(static_cast<long long>(first), static_cast<long long>(next));
  }
  return ll_pair(0, 0);
}

std::vector<bool> StepInPrimes::sieve;


void testequal(std::pair<long long, long long> ans,
  std::pair<long long, long long> sol)
{
  if (ans == sol)
  {
    std::cout << "Passed";
  }
  else
  {
    std::cout << "Failed";
  }
  std::cout << " {" << ans.first << ", " << ans.second << "}" << std::endl;
}

void dotest(int g, long long m, long long n,
  std::pair<long long, long long> const &expected)
{
  std::cout << "(" << g << ", " << m << ", " << n << ") {" << expected.first
    << ", " << expected.second << "}" << std::endl;
  testequal(StepInPrimes::step(g, m, n), expected);
}

void primes(size_t N, size_t max, size_t first = 0, size_t last = 0)
{
  StepInPrimes::calculate_sieve(max);
  std::cout << "primes(" << N << ", " << max << ", " << first << ", " << last << ")" << std::endl;
  auto w = 0;
  for (size_t i = 2, n = 0; n < N; ++i)
  {
    if (StepInPrimes::is_prime(i))
    {
      if (i >= first && (i < last || last == 0))
      {
        std::cout << std::setw(4) << i << ", ";
      }
      ++n;
      if (++w > 9)
      {
        if (i >= first && (i < last || last == 0))
        {
          std::cout << std::endl;
        }
        w = 0;
      }
    }
  }
}

void Test_Steps_In_Primes()
{
  primes(20, 100);
  primes(27, 101);

  dotest(2, 100, 110, { 101, 103 });
  dotest(11, 30000, 100000, { 0, 0 });
  primes(27, 100000, 29999, 30050);
  dotest(2, 2, 50, { 3, 5 });
  dotest(4, 100, 110, { 103, 107 });
  dotest(6, 100, 110, { 101, 107 });
  dotest(8, 300, 400, { 359, 367 });
  dotest(10, 300, 400, { 307, 317 });
};
