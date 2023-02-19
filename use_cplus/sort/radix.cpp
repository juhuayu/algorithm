#include <iostream>
// C中常量INT_MAX和INT_MIN分别表示最大、最小整数，定义在头文件limits.h中
#include <limits.h>
#include <math.h>
using namespace std;
// 桶

class Radix
{
private:
    // 取 x 上第 d 位上的数字
    int getDigit(int x, int d)
    {
        return ((x / int(pow(10, d - 1))) % 10);
    }

public:
    // 获取数组中最高位是多少
    int maxBits(int *arr, int len)
    {
        int max = INT_MIN; // 初始化为系统最小值
        for (int i = 0; i < len; i++) // 找最大值
        {
            max = std::max(max, arr[i]);
        }
        int res = 0;
        while (max != 0) // 看有多少位
        {
            res++;
            max /= 10;
        }
        return res;
    }
    void radixSort(int *arr, int L, int R, int digit)
    {
        const int radix = 10; // 以十进制为基础
        int i = 0, j = 0;
        int bucket[R - L + 1] = {0}; // 有多少个数准备多少个辅助空间
        for (int d = 1; d <= digit; d++)
        {
            // 10个空间
            // count[0] 当前位(d位)是(0)的数字有多少个
            // count[1] 当前位(d位)是(0和1)的数字有多少个
            // count[2] 当前位(d位)是(0，1和2)的数字有多少个
            // count[i] 当前位(d位)是(0~i)的数字有多少个
            int count[radix] = {0};
            // 统计对应位置词频（相当于入桶）
            for (i = L; i <= R; i++)
            {
                j = getDigit(arr[i], d);
                count[j]++;
            }
            for (i = 1; i < radix; i++) // 处理count数组为（前缀和）数组
            {
                count[i] = count[i] + count[i - 1];
            }
            // 出桶
            for (i = R; i >= L; i--) // 数组从右往左遍历
            {
                j = getDigit(arr[i], d); // 取出对应位置上的数字
                bucket[count[j] - 1] = arr[i]; // 将原数组中的值放到词频-1位置
                count[j]--; // 对应位置词频--
            }
            // 维持此次出桶的结果
            for (i = L, j = 0; i <= R; i++, j++) // 将辅助数组中的数倒到原数组中
            {
                arr[i] = bucket[j];
            }
        }
    }
};
