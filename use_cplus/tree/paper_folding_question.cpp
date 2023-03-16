#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "CreatTree.cpp"
using namespace std;
/*

#: 凹
*: 凸
在一张纸上对折，打印从上到下的折痕，N代表折了几次

*/
class PaaerFolding{
  public:
  void printAllFolds(int N) {
    prinfProcess(1, N, true);
  }
  // 递归过程，来到了某一个节点
  // i是节点的层数，N是一共有多少层，down=true 凹，down=false 凸
  void prinfProcess(int i, int N, bool down) {
    if (i>N)
    {
      return;
    }
    prinfProcess(i+1, N, true);
    cout << (down?'#':'*') << endl;
    prinfProcess(i+1, N, false);
  }
};

int main() {
  PaaerFolding pf;
  pf.printAllFolds(3);
  system("pause");
  return 0;
}