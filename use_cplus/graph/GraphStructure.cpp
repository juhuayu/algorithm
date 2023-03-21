#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Node;
class Edge {
 public:
  int weight;  // 权重
  Node* from;  // 开始节点
  Node* to;    // 结束节点
  Edge(int wei, Node* f, Node* t)
      : weight(wei), from(f), to(t) {}
};

class Node {
 public:
  int value;            // 自己的数据项
  int in;               // 入度
  int out;              // 出度
  vector<Node*> nexts;  // 由这个点发散连接的点集合
  vector<Edge*> edges;  // 由这个点发散连接的点的边集合
  Node(int val) {
    value = val;
    in = 0;
    out = 0;
    nexts = * new vector<Node*>;
    edges = * new vector<Edge*>;
  }
  Node() {
    value = -1;
    in = 0;
    out = 0;
    nexts = * new vector<Node*>;
    edges = * new vector<Edge*>;
  }
};

class Graph {
 private:
 public:
  unordered_map<int, Node*> nodes;
  unordered_set<Edge*> edges;

  Graph() {
    nodes = * new unordered_map<int, Node*>;
    edges = * new unordered_set<Edge*>;
  }
};
