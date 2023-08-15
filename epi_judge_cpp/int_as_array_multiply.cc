#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> Multiply(vector<int> num1, vector<int> num2) {
  // TODO - you fill in here.
  vector<int> result(num2.size(), 0);
  const int sign = num1[0] * num2[0] < 0 ? -1 : 1;

  for(int i = num1.size() - 1; i >= 0; i--) {
      for(int j = 0; j < num2.size(); j++) {
          result[j] += abs(num2[j] * num1[i]);
      }

      // handle the ripple carry
      for(int j = result.size() - 1; j > 0; j--) {
          if (result[j] > 9) {
              int carry = result[j] / 10;
              result[j] = result[j] % 10;
              result[j - 1] += carry;
          }
      }
      // handle the carry-out
      if(result[0] > 9) {
          int carry = result[0] / 10;
          result[0] = result[0] % 10;
          auto it = result.emplace(result.begin(), carry);
      } else {
          auto it = result.emplace(result.begin(), 0);
      }
      // handle the next digit
      num2.push_back(0);
  }

  // remove unnecessary zero
  auto it = result.begin();
  while(it != result.end()) {
      if(*it == 0) {
          result.erase(it);
      } else {
          break;
      }
  }
  if(result.size() == 0) {
      result.push_back(0);
  }

  result[0] *= sign;
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}

//int main() {
//    vector<int> num1(3);
//    num1[0] = 1, num1[1] = 2, num1[2] = 3;
//    vector<int> num2(3);
//    num2[0] = 9, num2[1] = 8, num2[2] = 7;
//
//
//    vector<int> result = Multiply(num1, num2);
//    std::cout << "result: ";
//    for(int i = 0; i < result.size(); i++) {
//        std::cout << result[i];
//    }
//    std::cout << std::endl;
//}
