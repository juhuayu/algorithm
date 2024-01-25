#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include "CreatGraph.cpp"
using namespace std;

class UseGraph {
 private:
 public:
  void bfs(Node* node);  // // 从node出发，宽度优先遍历
  void dfs(Node* node);  // // 从node出发，深度优先遍历
  list<Node*>* sortedTopology(Graph* graph); // 拓扑排序（有向图）
};
// 从node出发，宽度优先遍历
void UseGraph::bfs(Node* node) {
  if (node == nullptr)
    return;
  list<Node*> queue;
  // 优化：可以使用数组会更快，不用哈希表
  unordered_set<Node*> set;  // 为了保证同一个点不要多次进队列
  queue.push_back(node);
  set.insert(node);  // 把出发点放里面
  while (!queue.empty()) {
    Node* cur = queue.front();
    queue.pop_front();
    cout << cur->value << "-";
    for (Node* next : cur->nexts) {       // 遍历当前节点连接的节点表
      if (set.find(next) == set.end()) {  // 查看节点有没有注册到哈希表，没有就添加
        set.insert(next);
        queue.push_back(next);
      }
    }
  }
}

// 从node出发，深度优先遍历（逮着一条路往死里走）
void UseGraph::dfs(Node* node) {
  if (node == nullptr) {
    return;
  }
  stack<Node*> nodeStack;  // 创建一个栈
  unordered_set<Node*> set; // 保存走过的路
  nodeStack.push(node);
  set.insert(node);
  cout << node->value << "-";
  while (!nodeStack.empty()) {
    Node* cur = nodeStack.top();
    nodeStack.pop();
    for (Node* next : cur->nexts) {
      if (set.find(next) == set.end()) {
        nodeStack.push(cur); // 把当前节点再压回去
        nodeStack.push(next); // 把当前节点nexts数组中的一个也压到栈里
        set.insert(next); // 在哈希表中注册nexts数组中的这个节点
        cout << next->value << "-";
        break;
      }
    }
  }
}

// 拓扑排序(有向图)
list<Node*>* UseGraph::sortedTopology(Graph* graph) {
  unordered_map<Node*, int> inMap; // key:某一个node  value:剩余的入度
  list<Node*> zeroInQueue; // 只有入度为0的才可以进这个队列
  for(auto next = graph->nodes.begin(); next != graph->nodes.end(); ++next) {
    inMap.insert(pair<Node*, int>(next->second, next->second->in)); // 把图的原始点和对应的入度写入
    if(next->second->in == 0) { // 入度为0的直接放到zeroInQueue里（第一批入度为0的）
      zeroInQueue.push_back(next->second);
    }
  }

  list<Node*> *result = new list<Node*>();
  while(!zeroInQueue.empty()) {
    Node* cur = zeroInQueue.front();
    zeroInQueue.pop_front();
    result->push_back(cur);
    for(Node* next:cur->nexts) { // 擦掉这个入度为0的点的影响
      inMap.insert(pair<Node*, int>(next, inMap.at(next)-1)); // 将这个节点的连接点的集合nexts里的点全部将入度-1并加到inMap中去
      if(inMap.at(next) == 0) {
        zeroInQueue.push_back(next); // 擦除的过程中把入度减为0的点加到zeroInQueue中去
      }
    }
  }

  return result;
}

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
  Graph* myMap = cg.creat(arr); // 生成无向图
  Node* head = myMap->nodes.at(1);

  UseGraph uGraph;
  uGraph.dfs(head);

  cout << endl;
  list<Node*>* resList = uGraph.sortedTopology(myMap);
  list<Node*>::iterator itr = resList->begin();

  for(; itr!=resList->end(); ++itr) {
    cout << (*itr)->value << "-";
  }
  
  
  

  system("pause");
  return 0;
}