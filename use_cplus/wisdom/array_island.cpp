/*
岛问题
一个矩阵中只有0和1两种值，每个位置都可以和自己的上、下、左、右 四个位置相连，
如果有一片1连在一起，这个部分叫做一个岛，求一个矩阵中有多少个岛?

001010
111010
100100
000000
这个矩阵有三个岛

并行算法（多核CPU解决思路）：
例：
将矩阵从中间分成2半，
cpu1处理左边并记录矩阵右边界信息（记录右边界岛的感染来源），
cpu2处理右边并记录矩阵左边边界信息（记录左边界岛的感染来源），
处理完之后，将cpu1右和cpu2左边界上的信息做并查集，以来源做区分检查岛是否碰撞（碰撞了则合并）

A2222A C22222
200000 000002
20B22B C22222
202000 000000
20222B D22222
200000 000002
22222A D22222

cpu1找到2个岛（感染来源分别是A和B）
cpu2找到2个岛（感染来源分别是C和D）
一共有4个岛，记为 num=4
初始化并查集结构（A）（B）（C）（D）
有4个碰撞点  AC,BC,BD,AD
检查A和C在不在一个集合 - 合并（AC）（B）（D） num-1
检查B和C在不在一个集合 - 合并（ACB）（D） num-1
检查B和D在不在一个集合 - 合并（ACBD） num-1
检查A和D在不在一个集合 - 跳过
检查完所有碰撞点，num=1 所以一共有1个岛
*/

#include <iostream>
#include <vector>
using namespace std;

// 把这个岛都变成2（感染）
void infect(vector<vector<int>>& m, int i, int j, int N, int M) {
  if (i < 0 || i >= N || j < 0 || j >= M || m[i][j] != 1) {
    return;
  }
  // i,j 没越界且当前位置是1
  m[i][j] = 2;
  infect(m, i - 1, j, N, M); // 上
  infect(m, i + 1, j, N, M); // 下
  infect(m, i, j - 1, N, M); // 左
  infect(m, i, j + 1, N, M); // 右
}

int countIsLands(vector<vector<int>> m) {
  if (m.empty())
    return 0;
  int N = m.size();
  int M = m[0].size();
  int res = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (m[i][j] == 1) {
        res++;
        infect(m, i, j, N, M);
      }
    }
  }
  return res;
}
// 时间复杂度 O(N*M)
int main() {
  vector<vector<int>> arr = {
      {1, 0, 1, 1, 1, 0, 1},
      {1, 0, 1, 0, 0, 0, 1},
      {0, 0, 1, 0, 1, 1, 1},
      {0, 0, 0, 1, 1, 1, 0},
      {1, 1, 0, 0, 0, 0, 0}};  // 4个

  cout<< countIsLands(arr) << endl;

  system("pause");
  return 0;
}
