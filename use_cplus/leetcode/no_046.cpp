/*
全排列

给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> path;
    vector<bool> flag(nums.size(), false); // 表示这些数还没有被选择，当我们选定一个数的时候，就将这个数组的相应位置设置为 true
    int size = nums.size();
    dfs(nums, 0, size, path, res, flag);
    return res;
  }
  void dfs(vector<int> nums, int depth, int size, vector<int> path, vector<vector<int>> &res, vector<bool> &flag) {
    if(size == depth) {
      res.push_back(path);
      return;
    }
    for(int i=0; i<size; i++) {
      if(!flag[i]) {
        path.push_back(nums[i]);
        flag[i] = true;
        dfs(nums, depth+1, size, path, res, flag);
        flag[i] = false;
        path.pop_back();
      }
    }
  }


  vector<vector<int>> permute_leetcode_01(vector<int>& nums) {
    vector<vector<int>> result;
    int num = 0;
    sort(nums.begin(),nums.end());
    do{
      result.push_back(nums);
      num++;
    }while(next_permutation(nums.begin(),nums.end()));
    return result;
  }
};

int main() {
  vector<int> nums = {1, 2, 3};

  Solution so;
  vector<vector<int>> res = so.permute(nums);
  for(auto &row : res) {
    for(auto &el : row) {
      cout << el << " ";
    }
    cout << endl;
  }

  system("pause");
  return 0;
}