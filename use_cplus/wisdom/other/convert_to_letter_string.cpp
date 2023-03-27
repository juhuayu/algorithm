#include <iostream>
using namespace std;
/*
规定1和A对应、2和B对应、3和C对应
那么一个数字字符串比如”111"，就可以转化为”AAA”、“KA"和“AK”。
给定一个只有数字字符组成的字符串str，返回有多少种转化结果。
*/
int process(char* str, int i, int len) {
  // 来到了最后的位置
  if (i == len) {
    return 1;  // 返回之前的决定
  }
  if (str[i] == '0') {
    return 0;  // 之前的决定让此时没法做转化
  }
  cout << "now: " << str[i] << "    index: " << i << endl;
  if (str[i] == '1') {
    int res = process(str, i + 1, len);  // i自己作为单独的部分，后续有多少种方法
    if (i + 1 < len) {
      res += process(str, i + 1, len);  // i和i+1作为单独的部分，后续有多少种
    }
    return res;
  }
  if (str[i] == '2') {
    int res = process(str, i + 1, len);  // i自己作为单独的部分，后续有多少种方法
    if (i + 1 < len && str[i + 1] >= '0' && str[i + 1] <= '6') {
      res += process(str, i + 1, len);  // i和i+1作为单独的部分且不超26，后续有多少种
    }
    return res;
  }
  return process(str, i + 1, len);
}

int main() {
  char str[] = "123";
  
  int res = process(str, 0, 3);
  cout << res << endl;
  system("pause");
  return 0;
}
