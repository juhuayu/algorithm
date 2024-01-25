#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
  一块金条切成两半，是需要花费和长度数值一样的铜板。比如长度为20的金条，不管切成多大的两半，都要花费20个铜板
  一群人想整分整块金条，怎么分最省铜板？
  类如给定数组{10，20，30}，代表一共3个人，整块分金条长度为10+20+30=60
  金条要分成10，20，30三个部分，如果先把长度60的金条分成10和50，花费60，再把长度50的金条分成20和30，花费50，一共花费110铜板
  但如果先把长度60的金条分成30和30，花费60，再把长度30的金条分成20和10，花费30，一共花费90铜板
  输入一个数组，返回分割的最小代价
*/

class LessMoneySplitGold {
  public:
  int lessMoney(vector<int> arr) {
    priority_queue<int,vector<int>,greater<int>> pQ;
    for(int i=0; i<arr.size(); i++) {
      pQ.push(arr[i]);
    }
    int sum = 0;
    int cur = 0;
    while (pQ.size() > 1)
    {
      int temp = pQ.top();
      pQ.pop();
      cur = pQ.top();
      pQ.pop();
      cur += temp;
      sum += cur;
      pQ.push(cur);
    }
    return sum;
  }
};

int main() {
  vector<int> testArr{10, 20, 30};
  LessMoneySplitGold lmsg;
  cout << lmsg.lessMoney(testArr) << endl;
  

  system("pause");
  return 0;
}