/*
--------------------------------------------- 组合总和 ---------------------------------------------

给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。

candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 

对于给定的输入，保证和为 target 的不同组合数少于 150 个。
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
      int size = candidates.size();
      vector<int> path;
      vector<vector<int>> res;
      if(size == 0) return res;
      sort(candidates.begin(), candidates.end());
      dfs(candidates, 0, size, path, res, target);
      return res;
    }

    int dfs(vector<int>& candidates, int begin, int size, vector<int> path, vector<vector<int>> &res, int target) {
      // 刚好相减后等于0，是我们需要的组合
      if(target == 0) {
        res.push_back(path);
        return 0;
      }
      for(int i = begin; i < size; i++) {
        // 树结构的剪枝操作，如果 target 减去一个数得到负数，那么减去一个更大的树依然是负数，同样搜索不到结果
        int residue = target - candidates[i];
        if(residue < 0) break;
        path.push_back(candidates[i]);

        // --------------------------------------------
        // cout << "before recursion : ";
        // for(auto &count : path) {
        //   cout << count << " ";
        // }
        // cout << endl << " residue : " << residue << endl;
        // --------------------------------------------

        dfs(candidates, i, size, path, res, residue);
        path.pop_back();

        // --------------------------------------------
        // cout << "after recursion : ";
        // for(auto &count : path) {
        //   cout << count;
        // }
        // cout << endl << "--------------------------------" << endl;
        // --------------------------------------------
      }
      return 1;
    }
};

int main() {
  vector<int> start = {2, 3, 5};
  int target = 8;

  Solution so;
  vector<vector<int>> res = so.combinationSum(start, target);
  for(auto &row : res) {
    for(auto &el : row) {
      cout << el << " ";
    }
    cout << endl;
  }

  system("pause");
  return 0;
}