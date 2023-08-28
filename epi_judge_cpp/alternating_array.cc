#include <string>
#include <vector>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
using std::swap;
void Rearrange(vector<int>* A_ptr) {
  // TODO - you fill in here.
  vector<int> &A = *A_ptr;
  for(int i = 1; i < A.size(); i++) {
      if((i % 2 == 1 && A[i - 1] > A[i]) || (i % 2 == 0 && A[i - 1] < A[i])) {
          swap(A[i - 1], A[i]);
      }
  }
  return;
}
void CheckAnswer(const vector<int>& A) {
  for (int i = 0; i < A.size(); ++i) {
    if (i % 2) {
      if (A[i] < A[i - 1]) {
        throw TestFailure()
            .WithProperty(PropertyName::RESULT, A)
            .WithMismatchInfo(i, FmtStr("A[{}] <= A[{}]", i - 1, i),
                              FmtStr("{} > {}", A[i - 1], A[i]));
      }
      if (i + 1 < A.size()) {
        if (A[i] < A[i + 1]) {
          throw TestFailure()
              .WithProperty(PropertyName::RESULT, A)
              .WithMismatchInfo(i, FmtStr("A[{}] >= A[{}]", i, i + 1),
                                FmtStr("{} < {}", A[i], A[i + 1]));
        }
      }
    } else {
      if (i > 0) {
        if (A[i - 1] < A[i]) {
          throw TestFailure()
              .WithProperty(PropertyName::RESULT, A)
              .WithMismatchInfo(i, FmtStr("A[{}] >= A[{}]", i - 1, i),
                                FmtStr("{} < {}", A[i - 1], A[i]));
        }
      }
      if (i + 1 < A.size()) {
        if (A[i + 1] < A[i]) {
          throw TestFailure()
              .WithProperty(PropertyName::RESULT, A)
              .WithMismatchInfo(i, FmtStr("A[{}] <= A[{}]", i, i + 1),
                                FmtStr("{} > {}", A[i], A[i + 1]));
        }
      }
    }
  }
}

void RearrangeWrapper(TimedExecutor& executor, vector<int> A) {
  executor.Run([&] { Rearrange(&A); });

  CheckAnswer(A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(args, "alternating_array.cc", "alternating_array.tsv",
                         &RearrangeWrapper, DefaultComparator{}, param_names);
}

//int main() {
//    std::vector<int> array(8);
//    std::vector<int> *a_ptr;
//    array[0] = 8;
//    array[1] = 3;
//    array[2] = 5;
//    array[3] = 6;
//    array[4] = 1;
//    array[5] = 7;
//    array[6] = 9;
//    array[7] = 2;
//
//    std::cout << "Input: ";
//    for(int i = 0; i < array.size(); i++) {
//        std::cout << array[i] << " ";
//    }
//    std::cout << std::endl;
//
//    a_ptr = &array;
//    Rearrange(a_ptr);
//
//    std::cout << "Output: ";
//    for(int i = 0; i < array.size(); i++) {
//        std::cout << array[i] << " ";
//    }
//    std::cout << std::endl;
//}
