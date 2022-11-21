#include <iostream>
using namespace std;
 
// C 20221118
// 输入：[1,8,6,2,5,4,8,3,7]
// 预计输出： 49
// 超出时间限制
int maxArea(int* height, int heightSize) {
  int i, j, res_max = 0;
  for(i=0; i<heightSize; i++) {
    for(j=i; j<heightSize; j++) {
      // ---------------- C++ ----------------
      // if((j-i)*min(height[i],height[j]) > res_max) {
      //   res_max = (j-i)*min(height[i],height[j]);
      // }
      // ----------------- C -----------------
      if((j-i)*(height[i]<height[j]?height[i]:height[j]) > res_max) {
        res_max = (j-i)*(height[i]<height[j]?height[i]:height[j]);
      }
    }
  }
  return res_max;
}

// C 20221121
// 执行用时：76 ms, 在所有 C 提交中击败了 80.40% 的用户
// 内存消耗：11.4 MB, 在所有 C 提交中击败了 76.79% 的用户
int maxArea_ameliorate(int* height, int heightSize) {
  int i=0, j=heightSize-1, temp = 0, res_max = 0;
  while (i<j) {
    temp = (j - i) * (height[i]<height[j]?height[i]:height[j]);
    if (temp > res_max)
    {
      res_max = temp;
    }
    if (height[i] > height[j])
    {
      j--;
    } else {
      i++;
    }
  }
  return res_max;
}

int main()
{
    int arr[] = {1,8,6,2,5,4,8,3,7};
    // cout << "result:" << maxArea(arr, 9) << endl;
    cout << "result:" << maxArea_ameliorate(arr, 9) << endl;

    getchar();
    return 0;
}