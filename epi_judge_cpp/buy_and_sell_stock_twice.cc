#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockTwice(const vector<double>& prices) {
  // TODO - you fill in here.
  double profit_1 = 0, profit_2 = 0;
  for(int sell = 1, buy = 0, previousBuy = 0; sell < prices.size(); sell++) {
      if(prices[sell] - prices[buy] > profit_1) {
          if(profit_1 > profit_2 && buy != previousBuy) {
              profit_2 = profit_1;
          }
          profit_1 = prices[sell] - prices[buy];
          previousBuy = buy;
      } else if(prices[sell] < prices[buy]) {
          buy = sell;
      }
  }
  return profit_1 + profit_2;
}

//int main(int argc, char* argv[]) {
//  std::vector<std::string> args{argv + 1, argv + argc};
//  std::vector<std::string> param_names{"prices"};
//  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
//                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
//                         DefaultComparator{}, param_names);
//}

int main() {
    vector<double> prices(7);

    prices[0] = 2;
    prices[1] = 30;
    prices[2] = 15;
    prices[3] = 10;
    prices[4] = 8;
    prices[5] = 25;
    prices[6] = 80;
//    prices[7] = 14;
//    prices[8] = 13;
//    prices[9] = 15;

    std::cout << "maxProfit: " << BuyAndSellStockTwice(prices) << std::endl;
}
