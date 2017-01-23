#include <utility>
#include <vector>

class StepInPrimes
{
  public:
    static std::vector<bool> sieve; // integers 2..N

    static void calculate_sieve(size_t N);
    static bool is_prime(long long p);
    typedef std::pair<long long, long long> ll_pair;

    // if there are no such primes return {0, 0}
    static ll_pair step(int g, long long m, long long n);
};
