#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  // TODO - you fill in here.
  double maxProfit = 0;
  for(int sell = 0, buy = 0; sell < prices.size(); sell++) {
      if(prices[sell] - prices[buy] > maxProfit) {
          maxProfit = prices[sell] - prices[buy];
      } else if(prices[sell] < prices[buy]) {
          buy = sell;
      }
  }

  return maxProfit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}

//int main() {
//    vector<double> prices(10);
//    prices[0] = 310;
//    prices[1] = 315;
//    prices[2] = 275;
//    prices[3] = 295;
//    prices[4] = 260;
//    prices[5] = 270;
//    prices[6] = 290;
//    prices[7] = 230;
//    prices[8] = 255;
//    prices[9] = 250;
//
//    std::cout << "maxProfit: " << BuyAndSellStockOnce(prices) << std::endl;
//}

