#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // C++
    // 执行用时： 404 ms , 在所有 C++ 提交中击败了 9.74% 的用户
    // 内存消耗： 9.9 MB , 在所有 C++ 提交中击败了 78.38% 的用户
    vector<int> twoSum(vector<int>& nums, int target) {
        int i, j;
        vector<int> res;
        for (i = 0; i < nums.size(); i++)
        {
            for(j=i; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target)
                {
                    if(i==j) continue;
                    res.push_back(i);
                    res.push_back(j);
                    return res;
                }
            }
        }
        return res;
    }
};

int main()
{
    int i, j;
    int arr[4] = {2, 7, 11, 15};
    vector<int> num, result;
    Solution solution;
    for(i=0; i<4; i++) {
        num.push_back(arr[i]);
    }
    result = solution.twoSum(num, 9);
    for(j=0; j<2; j++) 
        cout<<result[j]<<endl;
    getchar();
    return 0;
}

