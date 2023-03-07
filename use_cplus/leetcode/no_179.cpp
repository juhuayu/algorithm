#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Cmper
{
  bool operator()(const int &x, const int &y)
  {
    // x:35   y:42
    long sx = 10, sy = 10;
    while (sx <= x)
    {
      sx *= 10;
    }
    while (sy <= y)
    {
      sy *= 10;
    }
    // x:35   y:42  sx:100   sy:100
    // 100*35+42    100*42+35
    return sy * x + y > sx * y + x;
  }
};
class Solution
{
public:
  string largestNumber(vector<int> &nums)
  {
    stable_sort(nums.begin(), nums.end(), Cmper());
    if (nums[0] == 0)
    {
      return "0";
    }
    string ret;
    for (int &x : nums)
    {
      ret += to_string(x);
    }
    return ret;
    for (int i = 0; i < nums.size(); i++)
    {
      cout << nums[i] << "-";
    }
    return "---";
  }
};

int main()
{
  vector<int> arr = {3, 30, 34, 5, 9}; // "9534330"
  Solution solution;
  solution.largestNumber(arr);

  system("pause");
  return 0;
}