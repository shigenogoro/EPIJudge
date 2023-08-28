#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
  // TODO - you fill in here.
  vector<int> primes;

  for(int i = 2; i <= n; i++) {
      bool isPrime = true;
      for(int j = 2; j * j <= i; j++) {
          if(i % j == 0) {
              isPrime = false;
              break;
          }
      }
      if(isPrime) {
          primes.push_back(i);
      }
  }

  return primes;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}

//int main() {
//    vector<int> result = GeneratePrimes(2);
//
//    for(int i = 0; i < result.size(); i++) {
//        std::cout << result[i] << " ";
//    }
//    std::cout << std::endl;
//}
