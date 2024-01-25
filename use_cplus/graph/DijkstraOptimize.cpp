/*
  使用堆来优化的Dijkstra算法
*/

#include <algorithm>  // 使用min函数
#include <iostream>
#include <vector>
#include "CreatGraph.cpp"
using namespace std;

class NodeRecord {
 public:
  Node* node;
  int distance;  // head到node点的最短距离
  NodeRecord(Node* n, int d)
      : node(n), distance(d) {}
};

class NodeHeap {
 private:
  vector<Node*> nodes;                     // 堆结构
  unordered_map<Node*, int> heapIndexMap;  // 节点在堆上的位置（查节点在不在堆上）
  unordered_map<Node*, int> distanceMap;   // head到表中node的最短距离
  int size = 0;                            // 当前堆上一共有多少个节点
  void insertHeapify(Node* node, int index);
  void heapify(int index, int size);
  void swap(int index1, int index2);  // 在堆上交换两个点的位置

 public:
  NodeHeap(int size);
  // 查看堆上这条记录存不存在，不存在就新增，存在就看更新还是不理睬
  void addOrUpdateOrIgnore(Node* node, int distance);
  bool isEmpty();               // 当前堆是否为空
  NodeRecord* pop();            // 弹出堆顶元素
  bool inHeap(Node*& node);     // node在不在堆上
  bool isEntered(Node*& node);  // node进没进来过堆
};

NodeHeap::NodeHeap(int size) {
  nodes.reserve(size);
}

// 发现了 head 到 node 新的距离 distance
void NodeHeap::addOrUpdateOrIgnore(Node* node, int distance) {
  if (inHeap(node)) {  // 节点在堆上(update)
    distanceMap.at(node) = min(distanceMap.at(node), distance);
    insertHeapify(node, heapIndexMap.at(node));
  }
  if (!isEntered(node)) {  // 这个节点就没有进过堆(add)
    nodes[size] = node;
    cout << "cur: " << (nodes[size]->value) << endl;
    heapIndexMap.insert(pair<Node*, int>(node, size));
    distanceMap.insert(pair<Node*, int>(node, distance));
    insertHeapify(node, size++);
  }
  // 啥都不做(ignore)
}
bool NodeHeap::isEmpty() {
  return size == 0;
}

NodeRecord* NodeHeap::pop() {
  Node* temp = new Node(nodes[0]);
  NodeRecord* nodeRecord = new NodeRecord(temp, distanceMap.at(nodes[0]));
  swap(0, size - 1);                      // 把堆的最后一个元素拿到堆顶
  heapIndexMap.at(nodes[size - 1]) = -1;  // 使用-1来标记这个节点进来过堆
  distanceMap.erase(nodes[size - 1]);
  free(nodes[size - 1]);
  heapify(0, --size);
  return nodeRecord;
}

bool NodeHeap::inHeap(Node*& node) {
  if (isEntered(node)) {
    if (heapIndexMap.at(node) != -1) {
      return true;
    }
  }
  return false;  // 进来又出去的节点值为-1
}

bool NodeHeap::isEntered(Node*& node) {
  return heapIndexMap.find(node) != heapIndexMap.end();
}

void NodeHeap::insertHeapify(Node* node, int index) {
  while (distanceMap.at(nodes[index]) < distanceMap.at(nodes[(index - 1) / 2])) {
    swap(index, (index - 1) / 2);
    index = (index - 1) / 2;
  }
}

void NodeHeap::heapify(int index, int size) {
  int left = index * 2 + 1;  // 左孩子下标
  while (left < size)        // 下方还有孩子的时候
  {
    int largest = left + 1 < size && distanceMap.at(nodes[left + 1]) > distanceMap.at(nodes[left]) ? left + 1 : left;  // 两个孩子中，谁的值大把下标给largest
    largest = distanceMap.at(nodes[largest]) > distanceMap.at(nodes[index]) ? largest : index;                         // 父和孩子之间，谁的值大把下标给largest

    if (largest == index)  // 如果还是父节点本身就退出
      break;
    swap(largest, index);
    index = largest;
    left = index * 2 + 1;
  }
}

void NodeHeap::swap(int index1, int index2) {
  heapIndexMap.at(nodes[index1]) = index2;
  heapIndexMap.at(nodes[index2]) = index1;
  Node* temp = nodes[index1];
  nodes[index1] = nodes[index2];
  nodes[index2] = temp;
}

class DijkstraOptimize {
 private:
 public:
  unordered_map<Node*, int>* dijkstra(Node* head, int size);
};
// 有size个节点
// 从head出发，所有head能到达的节点，生成到达每个节点的最小路径记录并返回
unordered_map<Node*, int>* DijkstraOptimize::dijkstra(Node* head, int size) {
  NodeHeap nodeHeap(size);
  nodeHeap.addOrUpdateOrIgnore(head, 0);
  unordered_map<Node*, int>* result = new unordered_map<Node*, int>;

  while (!nodeHeap.isEmpty()) {
    NodeRecord* record = nodeHeap.pop();
    Node* cur = record->node;
    int distance = record->distance;
    delete record;
    for (Edge* edge : cur->edges) {
      nodeHeap.addOrUpdateOrIgnore(edge->to, edge->weight + distance);
    }
    result->insert(pair<Node*, int>(cur, distance));
  }
  return result;
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

  DijkstraOptimize dj;
  unordered_map<Node*, int>* res = dj.dijkstra(myMap->nodes.at(1), 6);
  unordered_map<Node*, int>::iterator itr = res->begin();

  for (; itr != res->end(); itr++) {
    cout << (*itr).first->value << " : " << (*itr).second << endl;
  }

  system("pause");
  return 0;
}
