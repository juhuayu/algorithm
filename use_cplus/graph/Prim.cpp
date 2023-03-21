#include <algorithm>  // 使用sort函数
#include <vector>
#include <iostream>
#include "CreatGraph.cpp"
using namespace std;

bool cmp(Edge* o1, Edge* o2) {
  return o1->weight > o2->weight;
}

class Prim {
 private:
 public:
  unordered_set<Edge*>* mst(Graph* graph) {
    vector<Edge*> queue;           // 存放所有的边集合
    unordered_set<Node*> set;      // 查看取出来的点在不在最小生成树中
    unordered_set<Edge*> *result = new unordered_set<Edge*>;  // 最后使用到的边集

    for (auto next = graph->nodes.begin(); next != graph->nodes.end(); ++next) { // 这个for循环是为了兼顾森林，生成多颗最小生成树的
      if (set.find(next->second) == set.end()) { // 随便取出一个点放进去
        set.insert(next->second);

        cout << "start node:  " << next->second->value << endl;

        for (Edge* edge : next->second->edges) { // 这里使用小根堆会好一些，就不需要下面的排序
          queue.push_back(edge);
        }
        sort(queue.begin(), queue.end(), cmp); // 对边的权值进行排序

        while (!queue.empty()) {
          Edge* edge = queue.back(); // 取出一条边
          queue.pop_back();
          Node* toNode = edge->to;
          if (set.find(toNode) == set.end()) { // 看这条边的终点在不在集合里
            set.insert(toNode);
            result->insert(edge);
            for (Edge* &nextEdge : toNode->edges) { //将新加入点联通的边都加到边集中
              queue.push_back(nextEdge);
            }
            sort(queue.begin(), queue.end(), cmp); // 再对这个边集进行排序
          }
        }
      }
    }
    return result;
  }
};

int main() {
  /* 无向图
        A -- B -- C
        | \  |    |
        D -- E -- F
  */
  vector<vector<int>> arr = {
      {1, 2, 2},
      {2, 3, 7},
      {1, 4, 3},
      {1, 5, 4},
      {2, 5, 1},
      {3, 6, 6},
      {4, 5, 8},
      {5, 6, 5},

      {2, 1, 2},
      {3, 2, 7},
      {4, 1, 3},
      {5, 1, 4},
      {5, 2, 1},
      {6, 3, 6},
      {5, 4, 8},
      {6, 5, 5},
  };

  CreatGraph cg;
  Graph* myMap = cg.creat(arr);  // 生成无向图

  Prim pr;
  unordered_set<Edge*> *res = pr.mst(myMap);
  unordered_set<Edge*>::iterator itr = res->begin();

  for(; itr!=res->end(); itr++) {
    cout << (*itr)->weight << "-";
  }

  system("pause");
  return 0;
}