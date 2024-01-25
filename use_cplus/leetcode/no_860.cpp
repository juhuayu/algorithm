/*
----------------------------------- 柠檬水找零 -----------------------------------

在柠檬水摊上，每一杯柠檬水的售价为 5 美元。顾客排队购买你的产品，（按账单 bills 支付的顺序）一次购买一杯。

每位顾客只买一杯柠檬水，然后向你付 5 美元、10 美元或 20 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 5 美元。

注意，一开始你手头没有任何零钱。

给你一个整数数组 bills ，其中 bills[i] 是第 i 位顾客付的账。如果你能给每位顾客正确找零，返回 true ，否则返回 false 。
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  bool lemonadeChange(vector<int>& bills) {
    vector<int> wallet;
    for (int i = 0; i < bills.size(); i++) {
      if (!collectmoney(wallet, bills[i])) {
        return false;
      }
    }
    return true;
  }
  bool collectmoney(vector<int>& wallet, int money) {
    if (money == 5) {
      wallet.push_back(money);
      return true;
    }
    switch (money / 5) {
      case 2:
        for (int i = 0; i < wallet.size(); i++) {
          if (wallet[i] == 5) {
            wallet.erase(wallet.begin() + i);
            wallet.push_back(money);
            return true;
          }
        }
        break;
      case 4: {
        for (int i = 0; i < wallet.size(); i++) {
          if (wallet[i] == 10) {
            for (int j = 0; j < wallet.size(); j++) {
              if (wallet[j] == 5) {
                if (i > j) {
                  wallet.erase(wallet.begin() + i);
                  wallet.erase(wallet.begin() + j);
                } else {
                  wallet.erase(wallet.begin() + j);
                  wallet.erase(wallet.begin() + i);
                }
                wallet.push_back(money);
                return true;
              }
            }
          }
        }
        int findfive = count(wallet.begin(), wallet.end(), 5);
        if (findfive >= 3) {
          int count = 0;
          for (int i = 0; i < wallet.size(); i++) {
            if (wallet[i] == 5 && count < 3) {
              wallet.erase(wallet.begin() + i);
              i--;
              count++;
            }
          }
          wallet.push_back(money);
          return true;
        }
      } break;
      default:
        break;
    }
    return false;
  }

  bool lemonadeChange_leetcode_01(vector<int>& bills) {
    return all_of(bills.cbegin(), bills.cend(), [a = 0, b = 0](int i) mutable { return i == 5 ? ++a : i == 10 ? (++b, a--)
                                                                                                  : b         ? (b-- && a--)
                                                                                                              : ((a -= 3) > -1); });
  }

  bool lemonadeChange_leetcode_02(vector<int>& bills) {
    int five = 0, ten = 0;
    for (int b : bills) {
      if (b == 5)
        five++;  // 无需找零
      else if (b == 10)
        five--, ten++;  // 返还 5
      else if (ten)
        five--, ten--;  // 此时 b=20，返还 10+5
      else
        five -= 3;  // 此时 b=20，返还 5+5+5
      if (five < 0)
        return false;  // 无法正确找零
    }
    return true;
  }
};

int main() {
  vector<int> bills = {5, 5, 5, 10, 20};
  Solution solution;
  bool res = solution.lemonadeChange_leetcode_02(bills);
  cout << res << endl;

  system("pause");
  return 0;
}