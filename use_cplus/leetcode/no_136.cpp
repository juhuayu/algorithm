#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    // 数组中只有一种数出现了奇数次
    int singleNumber(vector<int> &nums)
    {
        int result = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            result ^= nums[i];
        }
        return result;
    }
    // 数组中只有两种数出现了奇数次
    void twoSingleNumber(vector<int> &nums)
    {
        int eor = singleNumber(nums);
        // eor = a^b  eor必不可能是0  eor上必然有一个位置上是1
        int rightOne = eor & (~eor + 1); // 提取最右侧的1（过程见《常规操作》）

        int onlyOne = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if ((rightOne & nums[i]) != 0) // 判断指定位置是否为1并进行异或运算，最后会得到其中一个奇数
            {
                onlyOne ^= nums[i];
            }
        }
        cout << onlyOne << "---" << (onlyOne ^ eor) << endl;
    }
};

int main()
{
    int i, j, result;
    int arr[5] = {2, 2, 4, 5, 4};
    vector<int> nums;
    Solution solution;
    for (i = 0; i < 5; i++)
    {
        nums.push_back(arr[i]);
    }
    result = solution.singleNumber(nums);
    cout << result << endl;

    int arrTwo[8] = {2, 3, 2, 5, 4, 9, 4, 3};
    vector<int> numsTwo(arrTwo, arrTwo + 8);
    solution.twoSingleNumber(numsTwo);
    getchar();
    return 0;
}
