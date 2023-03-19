#include <algorithm>  // 使用sort函数
#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include "CreatGraph.cpp"
using namespace std;

class MySet {
 public:
  unordered_map<Node*, list<Node*>> *setMap;

  MySet(list<Node*> const &nodes) {
    setMap = new unordered_map<Node*, list<Node*>>();
    for (Node* cur : nodes) {
      list<Node*> set;
      set.push_back(cur);
      setMap->insert(pair<Node*, list<Node*>>(cur, set));
    }
  }
  ~MySet() {
    delete setMap;
  }

  // 判断出发点和终点在不在一个集合里
  bool isSameSet(Node* &from, Node* &to) {
    list<Node*> &fromSet = setMap->at(from);
    list<Node*> &toSet = setMap->at(to);

    cout << "form:  " << from->value << endl;
    cout << "to  :  " << to->value << endl;
    list<Node*>::iterator itrFrom = fromSet.begin();
    for(; itrFrom!=fromSet.end(); itrFrom++) {
      cout << (*itrFrom)->value << "-";
    }
    cout << endl;
    list<Node*>::iterator itrTo = toSet.begin();
    for(; itrTo!=toSet.end(); itrTo++) {
      cout << (*itrTo)->value << "-";
    }
    cout << endl;
    cout << (fromSet == toSet) << endl;
    cout << "----------------------------" << endl;

    return fromSet == toSet;
  }
  // 合并from和to的点集（优化：使用并查集）
  void marge(Node* &from, Node* &to) {
    list<Node*> fromSet = setMap->at(from);
    list<Node*> toSet = setMap->at(to);
    for (Node* toNode : toSet) {
      fromSet.push_back(toNode);
    }
    for (Node* toNode : fromSet) {
      setMap->erase(toNode);
      setMap->insert(pair<Node*, list<Node*>>(toNode, fromSet));
    }
  }
};
bool cmp(Edge* o1, Edge* o2) {
  return o1->weight > o2->weight;
}
class Kruskal {
 private:
 public:
  unordered_set<Edge*>* mst(Graph* graph) {
    // 创建点的集合（初始化为每个点自己是一个集合）
    list<Node*> myList;
    for (auto next = graph->nodes.begin(); next != graph->nodes.end(); ++next) {
      myList.push_back(next->second);
    }
    MySet myset(myList);
    // 创建一个从小到大排序的边集合(优化：使用大根堆每加一个点调整一下)
    vector<Edge*> queue;
    for (Edge* edge : graph->edges) {
      queue.push_back(edge);
    }
    sort(queue.begin(), queue.end(), cmp);
    // 
    unordered_set<Edge*> *result = new unordered_set<Edge*>;
    // 把所有的边取一遍判断开始和结束点在不在一个集合里
    while (!queue.empty())
    {
      Edge* edge = queue.back(); // 取出当前集合中最小的边
      queue.pop_back();
      if(!myset.isSameSet(edge->from, edge->to)) { // 查看俩个点在不在一个集合里
        result->insert(edge);
        myset.marge(edge->from, edge->to); // 合并两个点的集合
      }
    }
    return result;
  }
};

int main() {
  /*
        A -- B -- C
        | \  |    |
        D -- E -- F
  */
  vector<vector<int>> arr = {
      {1, 2, 2},
      {2, 3, 7},
      {1, 4, 4},
      {1, 5, 4},
      {2, 5, 1},
      {3, 6, 6},
      {4, 5, 4},
      {5, 6, 5},
  };

  CreatGraph cg;
  Graph* myMap = cg.creat(arr);  // 生成无向图

  Kruskal kr;
  unordered_set<Edge*> *res = kr.mst(myMap);
  unordered_set<Edge*>::iterator itr = res->begin();

  for(; itr!=res->end(); itr++) {
    cout << (*itr)->weight << "-";
  }

  system("pause");
  return 0;
}