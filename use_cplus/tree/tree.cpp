#include <iostream>
#include <algorithm> // 主要使用 max() 函数
#include <limits.h> // 主要使用系统最小值
#include <stack>
#include <list>
#include <unordered_map>
using namespace std;

class Node {
 public:
  int value;    // 数据
  Node* left;   // 二叉树左节点
  Node* right;  // 二叉树右节点
  Node()
      : value(0), left(nullptr), right(nullptr) {}
  Node(int i)
      : value(i), left(nullptr), right(nullptr) {}
  Node(int i, Node* l, Node* r)
      : value(i), left(l), right(r) {}
};

class Tree {
 private:
  Node* head;
  void preOrderRecur(Node* now);  // 前序
  void inOrderRecur(Node* now);   // 中序
  void posOrderRecur(Node* now);  // 后序

  void preOrderUnRecur(Node* now);  // 非递归前序
  void inOrderUnRecur(Node* now);   // 非递归前序
  void posOrderUnRecur(Node* now);  // 非递归前序

  void rowOrder(Node* now); // 层序

 public:
  Tree();
  ~Tree();
  void creatTree();
  void printTree(int i);
  int getMaxWidthByHash(); // 求最大宽度（使用哈希表）
  int getMaxWidth(); // 求最大宽度（仅使用有限几个变量）
};

Tree::Tree() {
  head = new Node;
}

Tree::~Tree() {
  delete head;
}
// 打印树结构 1:前序 2:中序 3:后序
void Tree::printTree(int i) {
  switch (i) {
    case 1: {
      cout << "pre:";
      preOrderRecur(head);
      cout << endl;
    } break;
    case 2: {
      cout << "in:";
      inOrderRecur(head);
      cout << endl;
    } break;
    case 3: {
      cout << "pos:";
      posOrderRecur(head);
      cout << endl;
    } break;
    case 4: {
      cout << "pre:";
      preOrderUnRecur(head);
      cout << endl;
    } break;
    case 5: {
      cout << "in:";
      inOrderUnRecur(head);
      cout << endl;
    } break;
    case 6: {
      cout << "pos:";
      posOrderUnRecur(head);
      cout << endl;
    } break;
    case 7: {
      cout << "row:";
      rowOrder(head);
      cout << endl;
    }
    default:
      break;
  }
}
// 前序遍历 根左右
void Tree::preOrderRecur(Node* now) {
  if (now == nullptr)
    return;
  cout << now->value << "-";
  preOrderRecur(now->left);
  preOrderRecur(now->right);
}
// 中序遍历 左根右
void Tree::inOrderRecur(Node* now) {
  if (now == nullptr)
    return;
  inOrderRecur(now->left);
  cout << now->value << "-";
  inOrderRecur(now->right);
}
// 后序遍历 左右根
void Tree::posOrderRecur(Node* now) {
  if (now == nullptr)
    return;
  posOrderRecur(now->left);
  posOrderRecur(now->right);
  cout << now->value << "-";
}
// 非递归前序
void Tree::preOrderUnRecur(Node* now) {
  Node* cur = now;
  stack<Node*> st;  // 创建一个栈
  st.push(cur);
  while (!st.empty()) {
    cur = st.top();
    st.pop();
    cout << cur->value << "-";
    if (cur->right != nullptr) {
      st.push(cur->right);
    }
    if (cur->left != nullptr) {
      st.push(cur->left);
    }
  }
}
// 非递归中序
void Tree::inOrderUnRecur(Node* now) {
  Node* cur = now;
  stack<Node*> st;  // 创建一个栈
  while (!st.empty() || cur != nullptr) {
    if(cur != nullptr) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      cout << cur->value << "-";
      cur = cur->right;
    }
  }
}
// 非递归后序
void Tree::posOrderUnRecur(Node* now) {
  Node* cur = now;
  stack<Node*> st1;  // 创建一个栈
  stack<Node*> st2;  // 创建一个栈
  st1.push(cur);
  while (!st1.empty()) {
    cur = st1.top();
    st1.pop();
    st2.push(cur);
    if(cur->left != nullptr) {
      st1.push(cur->left);
    }
    if(cur->right != nullptr) {
      st1.push(cur->right);
    }
  }
  while (!st2.empty()) {
    cout << st2.top()->value << "-";
    st2.pop();
  }
}
// 层序遍历
void Tree::rowOrder(Node* now) {
  if(now == nullptr) return;
  list<Node*> nodeList; // 使用队列，先进先出
  nodeList.push_back(now);
  while (!nodeList.empty()) {
    Node* cur = nodeList.front();
    nodeList.pop_front(); // 出一个就打印，再把它的左右孩子进队
    cout << cur->value << "-";
    if(cur->left != nullptr) {
      nodeList.push_back(cur->left);
    }
    if(cur->right != nullptr) {
      nodeList.push_back(cur->right);
    }
  }
}
// 层序遍历 -> 求最大宽度（使用哈希表）
int Tree::getMaxWidthByHash() {
  if(head == nullptr) return 0;
  Node* now = head;
  list<Node*> nodeList;
  nodeList.push_back(now);
  unordered_map<Node*, int> levelMap;
  levelMap.insert(pair<Node*, int>(now, 1));
  int curLevel = 1; // 当前在哪一层
  int curLevelNodes = 0; // 当前层发现了几个节点
  int maxCount = INT_MIN;
  while (!nodeList.empty()) {
    Node* cur = nodeList.front();
    nodeList.pop_front();
    int curNodeLevel = levelMap.at(cur); // 查出该节点在第几层
    if(curNodeLevel == curLevel) {
      curLevelNodes++; // 同一层
    } else {
      maxCount = max(maxCount, curLevelNodes); // 来到了下一层，进行结算
      curLevel++;
      curLevelNodes = 1;
    }
    if(cur->left != nullptr) {
      levelMap.insert(pair<Node*, int>(cur->left, curNodeLevel+1));
      nodeList.push_back(cur->left);
    }
    if(cur->right != nullptr) {
      levelMap.insert(pair<Node*, int>(cur->right, curNodeLevel+1));
      nodeList.push_back(cur->right);
    }
  }
  return maxCount;
}
// 层序遍历 -> 求最大宽度（仅使用有限几个变量）
int Tree::getMaxWidth() {
  if(head == nullptr) return 0;
  Node* now = head;
  list<Node*> nodeList;
  nodeList.push_back(now);
  Node* nodeCurEnd = now; // 当前层的最后一个节点
  Node* nodeNextEnd = nullptr; // 下一层的最后一个节点
  int curLevelNode = 0;
  int maxCount = 0;
  while (!nodeList.empty()) {
    Node* cur = nodeList.front();
    nodeList.pop_front();
    if(cur->left != nullptr) {
      nodeList.push_back(cur->left);
      nodeNextEnd = cur->left;
    }
    if(cur->right != nullptr) {
      nodeList.push_back(cur->right);
      nodeNextEnd = cur->right; // nodeNextEnd 永远设置为最后一个进队列的
    }
    curLevelNode++;
    if(cur == nodeCurEnd) { // 当前节点是不是本层最后一个节点
      maxCount = max(maxCount, curLevelNode);
      nodeCurEnd = nodeNextEnd; // 下一层最后一个节点给本层
      nodeNextEnd = nullptr;
      curLevelNode = 0;
    }
  }
  return maxCount;
}
void Tree::creatTree() {
  /*
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
            /   \
           8     9
  */
  Node* n9 = new Node(9);
  Node* n8 = new Node(8);
  Node* n7 = new Node(7);
  Node* n6 = new Node(6);
  n6->right = n9;
  Node* n5 = new Node(5);
  n5->left = n8;
  Node* n4 = new Node(4);
  Node* n3 = new Node(3, n6, n7);
  Node* n2 = new Node(2, n4, n5);
  head->value = 1;
  head->left = n2;
  head->right = n3;
}

int main() {
  Tree tree;
  tree.creatTree();
  cout << tree.getMaxWidth() << endl;
  // tree.printTree(6);
  system("pause");
  return 0;
}