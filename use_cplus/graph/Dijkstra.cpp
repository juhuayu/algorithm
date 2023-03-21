// 适用范围：
// 权值可以出现负数的边但不能出现累加和为负数的环

#include <limits.h>
#include <algorithm>  // 使用min函数
#include <iostream>
#include <vector>
#include "CreatGraph.cpp"
using namespace std;

class Dijkstra {
 private:
 public:
  unordered_map<Node*, int>* dijkstra(Node* head);
  Node* getMinDistanceAndUnSelectedNodes(unordered_map<Node*, int>* const distanceMap, unordered_set<Node*> const& touchedNodes);
};

unordered_map<Node*, int>* Dijkstra::dijkstra(Node* head) {
  // 从head出发到所有点的最小距离
  // key：从head出发到达key    value：从head出发到达key的最小距离
  unordered_map<Node*, int>* distanceMap = new unordered_map<Node*, int>;
  distanceMap->insert(pair<Node*, int>(head, 0));
  // 已经求过距离的节点，存在selectedNodes中，以后再也不碰（注册）
  unordered_set<Node*> selectedNodes;
  Node* minNode = getMinDistanceAndUnSelectedNodes(distanceMap, selectedNodes);
  while (minNode->value != -1) {  // 在新建图的时候，默认空点值为-1，正常应该是判断是否等于null
    int distance = distanceMap->at(minNode);
    for (Edge* edge : minNode->edges) {                                          // 考察取出来这个点的所有边
      Node* toNode = edge->to;                                                   // 取出这条边的终点
      if (distanceMap->find(toNode) == distanceMap->end()) {                     // 看这个终点有没有在距离表中，没有就是正无穷
        distanceMap->insert(pair<Node*, int>(toNode, distance + edge->weight));  // 添加这个点
      } else {
        int temp = distanceMap->at(toNode);
        distanceMap->erase(edge->to);
        distanceMap->insert(pair<Node*, int>(edge->to, min(temp, distance + (edge->weight))));
      }
    }
    selectedNodes.insert(minNode);  // 注册这个点，再也不碰
    minNode = getMinDistanceAndUnSelectedNodes(distanceMap, selectedNodes);
  }
  return distanceMap;
}
// 在distanceMap中找一条最小的记录，且这条记录不能是被注册过的
Node* Dijkstra::getMinDistanceAndUnSelectedNodes(unordered_map<Node*, int>* const distanceMap, unordered_set<Node*> const& touchedNodes) {
  // unordered_map<Node*, int>::iterator itr = distanceMap->begin();
  // for (; itr != distanceMap->end(); itr++) {
  //   cout << ((*itr).first->value) << "-";
  // }

  Node* minNode = new Node;
  int minDistance = INT_MAX;
  for (pair<Node*, int> entry : *distanceMap) {  // 遍历所有记录找没有注册过的最短记录
    Node* node = entry.first;
    int distance = entry.second;
    // 这个点没有被注册且距离变得更小
    if ((touchedNodes.find(node) == touchedNodes.end()) && distance < minDistance) {
      minNode = node;
      minDistance = distance;
    }
  }
  return minNode;
}

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
  cout << myMap->nodes.at(1)->value << endl;

  Dijkstra dj;
  unordered_map<Node*, int>* res = dj.dijkstra(myMap->nodes.at(1));
  unordered_map<Node*, int>::iterator itr = res->begin();

  for (; itr != res->end(); itr++) {
    cout << (*itr).first->value << " : " << (*itr).second << endl;
  }

  system("pause");
  return 0;
}