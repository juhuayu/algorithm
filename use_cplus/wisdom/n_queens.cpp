/*
  经典N皇后问题
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 不可能存在共行，只需要看共不共列，共不共斜线
// record[0...i-1] 需要看，// record[i...] 不需要看
// 返回i行皇后，放在了j列，是否有效
bool isValid(vector<int> const &record, int i, int j) {
  for (int k = 0; k < i; k++) { // 之前的某个k行的皇后
    if (j == record[k] || abs(record[k] - j) == abs(i - k)) { // 行坐标相减的绝对值和纵坐标相减的绝对值相等的话一定是45度共斜线的
      return false;
    }
  }
  return true;
}

// record[0...i-1]的皇后任何两个皇后一定不共行，不共列，不共斜线

// i：当前来到了第i行
// record[0...i-1]：我之前摆的皇后
// n：一共有多少行
// return：摆完所有的皇后合法的摆法有多少种
int process(int i, vector<int> &record, int n) {
  if (i == n)
    return 1;  // 来到了终止行（最后一行的下一行）
  int res = 0;
  for (int j = 0; j < n; j++) {  // j表示列，当前在第i行，尝试i行上所有的列
    if (isValid(record, i, j)) {
      record[i] = j;
      res += process(i + 1, record, n);
    }
  }
  return res;
}

int start(int n) {
  if (n < 1)
    return 0;
  vector<int> record(n);  // record[i] 表示第i行的皇后放在了第几列
  return process(0, record, n);
}

int main() {
  cout << start(5) << endl;
  system("pause");
  return 0;
}