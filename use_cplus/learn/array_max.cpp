#include <iostream>
using namespace std;

class GetMaxFun
{
private:
  /* data */
public:
  int GetMax(int *arr, int len) {
    return process(arr, 0, len-1);
  }
  // 在arr[L...R]范围上求最大值
  int process(int *arr, int L, int R) {
    if(L == R) {
      return arr[L];
    }
    int mid = L+((R-L) >> 1);
    int leftMax = process(arr, L, mid);
    int rightMax = process(arr, mid+1, R);
    return leftMax>rightMax?leftMax:rightMax;
  }
};

