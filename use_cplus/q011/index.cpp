#include <iostream>
using namespace std;
 
// C
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

int main()
{
    int arr[] = {1,8,6,2,5,4,8,3,7};
    cout << "result:" << maxArea(arr, 9) << endl;

    getchar();
    return 0;
}