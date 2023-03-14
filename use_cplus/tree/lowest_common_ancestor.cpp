#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include "CreatTree.cpp"
using namespace std;

class LowestCommonAncestor {
 private:
  void lca_process(Node* head, unordered_map<Node*, Node*> &fatherMap);

 public:
  LowestCommonAncestor();
  ~LowestCommonAncestor();
  void rowOrder(Node* head);

  Node* get_lca(Node* head, Node* o1, Node* o2);
  Node* get_lca_node(Node* head, Node* o1, Node* o2);
};

LowestCommonAncestor::LowestCommonAncestor() {
}

LowestCommonAncestor::~LowestCommonAncestor() {
}
// 层序打印
void LowestCommonAncestor::rowOrder(Node* head) {
  if (head == nullptr)
    return;
  list<Node*> nodeList;  // 使用队列，先进先出
  nodeList.push_back(head);
  while (!nodeList.empty()) {
    Node* cur = nodeList.front();
    nodeList.pop_front();  // 出一个就打印，再把它的左右孩子进队
    cout << cur->value << "-";
    if (cur->left != nullptr) {
      nodeList.push_back(cur->left);
    }
    if (cur->right != nullptr) {
      nodeList.push_back(cur->right);
    }
  }
  cout << endl;
}

// o1和o2一定属于head为头的树
// 返回o1和o2的最低公共祖先（向上查找第一个公共祖先）
Node* LowestCommonAncestor::get_lca(Node* head, Node* o1, Node* o2) {
  // 设置一个存储了所有节点父节点的哈希表
  unordered_map<Node*, Node*> fatherMap;
  fatherMap.insert(pair<Node*, Node*>(head, head));
  lca_process(head, fatherMap);
  // 再创建一个哈希表存储o1向上查找的所有的路径点
  unordered_set<Node*> setMap;
  setMap.insert(o1);
  Node* cur = o1;
  while (cur != fatherMap.at(cur)) {
    setMap.insert(cur);
    cur = fatherMap.at(cur);
  }
  setMap.insert(head);  // 最后只有根节点不在哈希表中，需要放进去
  // o2开始向上查找，每查找一个节点就去o1路径点中查看有没有，有就返回，没有就继续向上查
  cur = o2;
  while (cur != head) {
    if (setMap.find(cur) != setMap.end()) {
      return cur;
    }
    cur = fatherMap.at(cur);
  }
  return head;
}
// 生成树节点对应父节点的哈希表
void LowestCommonAncestor::lca_process(Node* head, unordered_map<Node*, Node*> &fatherMap) {
  if (head == nullptr) {
    return;
  }
  fatherMap.insert(pair<Node*, Node*>(head->left, head));
  fatherMap.insert(pair<Node*, Node*>(head->right, head));
  lca_process(head->left, fatherMap);
  lca_process(head->right, fatherMap);
}
/*
情况1：O1是O2的公共最低节点或O2是O1的公共最低节点
情况2：O1和O2不互为公共最低节点，需要向上查才能找到
例：
树结构                      递归返回的过程（N代表空）
              A                            B
            /   \                        /   \
           B     C                      B     N
          / \     \                    / \     \
        O1   D     E                 O1  O2     N
            / \                         /  \
           F   G                       N   O2
                \                            \
                 O2                           O2
*/
Node* LowestCommonAncestor::get_lca_node(Node* head, Node* o1, Node* o2) {
  if (head == nullptr || head == o1 || head == o2) {
    return head;
  }
  Node* left = get_lca_node(head->left, o1, o2);
  Node* right = get_lca_node(head->right, o1, o2);

  if (left != nullptr && right != nullptr) {
    return head;
  }
  return left != nullptr ? left : right;
}

int main() {
  CreatTree tree1;
  ReturnType_LCA* testTree = tree1.creatTestTree_lca();

  LowestCommonAncestor lca;
  lca.rowOrder(testTree->head);

  Node* res1 = lca.get_lca(testTree->head, testTree->o1, testTree->o2);
  Node* res2 = lca.get_lca_node(testTree->head, testTree->o1, testTree->o2);
  
  cout << "res1:" << res1->value << endl;
  cout << "res2:" << res2->value << endl;

  system("pause");
  return 0;
}