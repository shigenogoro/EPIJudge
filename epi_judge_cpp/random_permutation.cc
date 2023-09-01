#include <functional>
#include <vector>
#include <random>

#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::bind;
using std::vector;
using std::swap;

void RandomSampling(int k, vector<int> *A_ptr) {
    vector<int> &A = *A_ptr;
    // Random Number Generator
    std::default_random_engine seed((std::random_device())());

    // Generator random index in [k, A.size() - 1]
    for(int i = 0; i < k; i++) {
        int randomIndex = std::uniform_int_distribution<int> {
                i, static_cast<int>(A.size() - 1)
        }(seed);

        swap(A[i], A[randomIndex]);
    }
    return;
}

vector<int> ComputeRandomPermutation(int n) {
  // TODO - you fill in here.
  vector<int> permutation(n);
  // Initialize permutation vector to 0, 1, 2, ..., n - 1
  for(int i = 0; i < n; i++) {
      permutation[i] = i;
  }
  RandomSampling(n, &permutation);

  return permutation;
}
int Factorial(int n) { return n <= 1 ? 1 : n * Factorial(n - 1); }

int PermutationIndex(vector<int> perm) {
  int idx = 0;
  int n = perm.size();
  for (int i = 0; i < perm.size(); ++i) {
    int a = perm[i];
    idx += a * Factorial(n - 1);
    for (int j = i + 1; j < perm.size(); ++j) {
      if (perm[j] > a) {
        --perm[j];
      }
    }
    --n;
  }
  return idx;
}

bool ComputeRandomPermutationRunner(TimedExecutor& executor, int n) {
  using namespace test_framework;
  vector<vector<int>> results;

  executor.Run([&] {
    for (int i = 0; i < 1000000; ++i) {
      results.emplace_back(ComputeRandomPermutation(n));
    }
  });

  vector<int> sequence;
  for (const vector<int>& result : results) {
    sequence.emplace_back(PermutationIndex(result));
  }
  return CheckSequenceIsUniformlyRandom(sequence, Factorial(n), 0.01);
}

void ComputeRandomPermutationWrapper(TimedExecutor& executor, int n) {
  RunFuncWithRetries(
      std::bind(ComputeRandomPermutationRunner, std::ref(executor), n));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "n"};
  return GenericTestMain(
      args, "random_permutation.cc", "random_permutation.tsv",
      &ComputeRandomPermutationWrapper, DefaultComparator{}, param_names);
}
