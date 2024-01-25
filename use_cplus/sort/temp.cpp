#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
 public:
  void backtrack(vector<vector<string>>& res, vector<string>& output, int first, int len) {
    // 所有数都填完了
    if (first == len) {
      res.emplace_back(output);
      cout << output[0] << endl;
      return;
    }
    for (int i = first; i < len; ++i) {
      // 动态维护数组
      swap(output[i], output[first]);
      // 继续递归填下一个数
      backtrack(res, output, first + 1, len);
      // 撤销操作
      swap(output[i], output[first]);
    }
  }
  vector<vector<string>> permute(vector<string>& nums) {
    vector<vector<string>> res;
    backtrack(res, nums, 0, (int)nums.size());
    return res;
  }
};

int main() {
  vector<string> haha = {"a","b","c"};
  Solution so;
  vector<vector<string>> res = so.permute(haha);
  system("pause");
  return 0;
}