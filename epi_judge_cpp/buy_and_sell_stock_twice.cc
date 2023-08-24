#include <vector>
#include <limits>

#include "test_framework/generic_test.h"
using std::vector;
using std::max;
using std::min;
using std::numeric_limits;
double BuyAndSellStockTwice(const vector<double>& prices) {
  // TODO - you fill in here.
  double maxTotalProfit = 0;
  vector<double> firstBuySellProfits(prices.size(), 0);
  double minPriceSoFar = numeric_limits<double>::max();

  /*
   * forward iteration:
   * the most profit that can be made with a single buy and sell by Day i (inclusive)
   * */
  for(int i = 0; i < prices.size(); i++) {
      minPriceSoFar = min(minPriceSoFar, prices[i]);
      maxTotalProfit = max(maxTotalProfit, prices[i] - minPriceSoFar);
      firstBuySellProfits[i] = maxTotalProfit;
  }

  /*
   * reverse iteration:
   * Working backward, the most profit that can be made with a single buy and sell on or after Day i
   * */
  double maxPriceSoFar = numeric_limits<double>::min();
  for(int i = prices.size() - 1; i >= 0; i--) {
      maxPriceSoFar = max(maxPriceSoFar, prices[i]);
      maxTotalProfit = max(maxTotalProfit, maxPriceSoFar - prices[i] + firstBuySellProfits[i - 1]);
  }

  return maxTotalProfit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
