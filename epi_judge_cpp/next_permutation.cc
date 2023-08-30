#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::swap;
vector<int> NextPermutation(vector<int> perm) {
  // TODO - you fill in here.
  // Step1: Find the start entry that has the longest decreasing suffix from the right
  int pivotEntry = 0;
  for(int i = perm.size() - 2; i >= -1; i--) {
      if(perm[i] < perm[i + 1]) {
          pivotEntry = i;
          break;
      } else if(i < 0) {
          pivotEntry = -1;
      }
  }
  // the perm is the largest permutation -> next permutation is null
  if(pivotEntry == -1) {
      return {};
  }

  // Step 2: Find the smallest entry such that perm[smallestEntry] > perm[pivotEntry]
  int smallestEntry = pivotEntry + 1;
  for(int i = pivotEntry + 2; i < perm.size(); i++) {
      if(perm[i] > perm[pivotEntry] && perm[smallestEntry] > perm[i]) {
          smallestEntry = i;
      }
  }

  // Step 3: Swap perm[smallestEntry] and perm[pivotEntry]
  swap(perm[smallestEntry], perm[pivotEntry]);

  // Step 4: Reverse the sequence after position pivotEntry -> sort the entries in the suffix from smallest to largest
  sort(perm.begin() + pivotEntry + 1, perm.end());

  return perm;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm"};
  return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
                         &NextPermutation, DefaultComparator{}, param_names);
}
