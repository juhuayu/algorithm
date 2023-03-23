/*
  优化了常数时间的N皇后问题
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
// 假如在第一行点了一个皇后 0000 0100
//   那么在下一行列的限制是 0000 0100
//            左斜线的限制 0000 1000
//            右斜线的限制 0000 0010
//            三个限制求或 0000 1110 所有的1位置是不能放皇后的
//
// colLim：列的限制，1的位置不能放皇后，0的位置可以
// leftDiaLim：左斜线的限制，1的位置不能放皇后，0的位置可以
// rightDiaLim：左斜线的限制，1的位置不能放皇后，0的位置可以
int process(int limit, int colLim, int leftDiaLim, int rightDiaLim) {
  if (colLim == limit) {  // 因为同一列上不能放皇后，所以当相等的时候说明有一种有效的摆法
    return 1;
  }
  int mostRightOne = 0;
  // (colLim | leftDiaLim | rightDiaLim) 列限制|左斜线限制|右斜线限制，即总限制（1代表不能放皇后，0可以放）
  // (~(colLim | leftDiaLim | rightDiaLim)) 取反（0代表不能放皇后，1可以放） 注：求反后前面全部变为了1
  // limit & (~(colLim | leftDiaLim | rightDiaLim)) 可以选择皇后的位置 注：取反后前面的1需要根据limit规定可以尝试的位置，不能尝试的位置变回0
  //                  limit 0000 1111 1111  （8皇后问题）
  //              列的限制是 0000 0000 0100
  //            左斜线的限制 0000 0000 1000
  //            右斜线的限制 0000 0000 0010
  //            三个限制求或 0000 0000 1110
  //                    取反 1111 1111 0001
  //             与limit求与 0000 1111 0001 （1就是在下一行可以放皇后的位置）
  int pos = limit & (~(colLim | leftDiaLim | rightDiaLim)); // 所有可以填皇后位置的位信息（候选皇后）
  int res = 0;
  while (pos != 0) { // 尝试所有1位置
    mostRightOne = pos & (~pos + 1); // 提取最右侧的1
    pos = pos - mostRightOne; // 减去尝试的当前位置
    res += process(limit, colLim | mostRightOne, (leftDiaLim | mostRightOne) << 1, (rightDiaLim | mostRightOne) >> 1); // 加入当前点的限制
  }
  return res;
}

// 不要超过32皇后问题，超过的话就需要替换为long类型
int start(int n) {
  if (n < 1 || n > 32) {
    return 0;
  }
  // 是几皇后问题，这个数的后多少位就都是1，前面的都是0
  int limit = n == 32 ? -1 : (1 << n) - 1;  // 限制右侧哪些区域是可以尝试的位置
  return process(limit, 0, 0, 0);
}

int main() {
  cout << start(5) << endl;
  system("pause");
  return 0;
}