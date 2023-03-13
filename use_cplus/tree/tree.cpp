#include <limits.h>   // 主要使用系统最小值
#include <algorithm>  // 主要使用 max() 函数
#include <iostream>
#include <list>
#include <stack>
#include <unordered_map>
using namespace std;
// ----------- 判断是否为平衡二叉树的返回类型 -----------
class ReturnType {
 public:
  bool isBalanced;
  int height;
  ReturnType(bool isB, int h)
      : isBalanced(isB), height(h) {}
};
// ----------- 判断是否为搜索二叉树的返回类型 -----------
class ReturnData {
 public:
  bool isBST;
  int min, max;
  ReturnData(bool is, int mi, int ma)
      : isBST(is), min(mi), max(ma) {}
};
// ------------ 判断是否为满二叉树的返回类型 ------------
class ReturnInfo {
 public:
  int height, nodes;
  ReturnInfo(int h, int n)
      : height(h), nodes(n) {}
};
// --------------------- 树节点结构 ---------------------
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
  static int preValue;
  void preOrderRecur(Node* now);  // 前序
  void inOrderRecur(Node* now);   // 中序
  void posOrderRecur(Node* now);  // 后序

  void preOrderUnRecur(Node* now);  // 非递归前序
  void inOrderUnRecur(Node* now);   // 非递归前序
  void posOrderUnRecur(Node* now);  // 非递归前序

  void rowOrder(Node* now);  // 层序

  ReturnType* process(Node* x);      // 是否为平衡二叉树的递归体
  ReturnData* process_bst(Node* x);  // 是否为搜索二叉树的递归体
  ReturnInfo* process_full(Node* x); // 是否为满二叉树的递归体

 public:
  Tree();
  ~Tree();
  void creatTree();
  void printTree(int i);
  int getMaxWidthByHash();  // 求最大宽度（使用哈希表）
  int getMaxWidth();        // 求最大宽度（仅使用有限几个变量）

  bool isBST(bool isRecur);      // 外部调用-是否为搜索树
  bool isBST(Node* cur);         // 是否是搜索二叉树递归
  bool isBSTUnRecur(Node* cur);  // 非递归

  bool isCBT();          // 是否是完全二叉树
  bool isBalanceTree();  // 是否为平衡二叉树
  bool isSelectTree();   // 是否为搜索二叉树（另一种递归）
  bool isFullTree();     // 是否为满二叉树
};
int Tree::preValue = INT_MIN;
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
    if (cur != nullptr) {
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
    if (cur->left != nullptr) {
      st1.push(cur->left);
    }
    if (cur->right != nullptr) {
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
  if (now == nullptr)
    return;
  list<Node*> nodeList;  // 使用队列，先进先出
  nodeList.push_back(now);
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
}
// 层序遍历 -> 求最大宽度（使用哈希表）
int Tree::getMaxWidthByHash() {
  if (head == nullptr)
    return 0;
  Node* now = head;
  list<Node*> nodeList;
  nodeList.push_back(now);
  unordered_map<Node*, int> levelMap;
  levelMap.insert(pair<Node*, int>(now, 1));
  int curLevel = 1;       // 当前在哪一层
  int curLevelNodes = 0;  // 当前层发现了几个节点
  int maxCount = INT_MIN;
  while (!nodeList.empty()) {
    Node* cur = nodeList.front();
    nodeList.pop_front();
    int curNodeLevel = levelMap.at(cur);  // 查出该节点在第几层
    if (curNodeLevel == curLevel) {
      curLevelNodes++;  // 同一层
    } else {
      maxCount = max(maxCount, curLevelNodes);  // 来到了下一层，进行结算
      curLevel++;
      curLevelNodes = 1;
    }
    if (cur->left != nullptr) {
      levelMap.insert(pair<Node*, int>(cur->left, curNodeLevel + 1));
      nodeList.push_back(cur->left);
    }
    if (cur->right != nullptr) {
      levelMap.insert(pair<Node*, int>(cur->right, curNodeLevel + 1));
      nodeList.push_back(cur->right);
    }
  }
  return maxCount;
}
// 层序遍历 -> 求最大宽度（仅使用有限几个变量）
int Tree::getMaxWidth() {
  if (head == nullptr)
    return 0;
  Node* now = head;
  list<Node*> nodeList;
  nodeList.push_back(now);
  Node* nodeCurEnd = now;       // 当前层的最后一个节点
  Node* nodeNextEnd = nullptr;  // 下一层的最后一个节点
  int curLevelNode = 0;
  int maxCount = 0;
  while (!nodeList.empty()) {
    Node* cur = nodeList.front();
    nodeList.pop_front();
    if (cur->left != nullptr) {
      nodeList.push_back(cur->left);
      nodeNextEnd = cur->left;
    }
    if (cur->right != nullptr) {
      nodeList.push_back(cur->right);
      nodeNextEnd = cur->right;  // nodeNextEnd 永远设置为最后一个进队列的
    }
    curLevelNode++;
    if (cur == nodeCurEnd) {  // 当前节点是不是本层最后一个节点
      maxCount = max(maxCount, curLevelNode);
      nodeCurEnd = nodeNextEnd;  // 下一层最后一个节点给本层
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

// 中序遍历 -> 是否是搜索二叉树（左节点<根节点<右节点）
bool Tree::isBST(bool isRecur) {
  if (isRecur) {
    return isBST(head);
  } else {
    return isBSTUnRecur(head);
  }
}
bool Tree::isBST(Node* cur) {
  if (cur == NULL) {
    return true;
  }
  bool isLeftBST = isBST(cur->left);  // 看左树是不是搜索二叉树
  if (!isLeftBST) {
    return false;
  }
  if (cur->value <= preValue) {  // 上一次遍历到的值是不是比当前的值大（中序：左根右）
    return false;
  } else {
    preValue = cur->value;
  }
  return isBST(cur->right);
}
// 中序遍历 -> 是否是搜索二叉树非递归
bool Tree::isBSTUnRecur(Node* cur) {
  int preValueNow = INT_MIN;
  stack<Node*> st;  // 创建一个栈
  while (!st.empty() || cur != nullptr) {
    if (cur != nullptr) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      // ---------- 中序遍历的改动 ----------
      if (cur->value <= preValueNow) {
        return false;
      } else {
        preValueNow = cur->value;
      }
      // -----------------------------------
      cur = cur->right;
    }
  }
}

// 层序遍历 -> 是否是完全二叉树
bool Tree::isCBT() {
  if (head == nullptr)
    return true;
  Node* cur = head;
  Node* l = nullptr;
  Node* r = nullptr;
  list<Node*> queue;
  bool left = false;  // 是否遇到左右孩子不全的标记
  queue.push_back(cur);
  while (!queue.empty()) {
    cur = queue.front();
    queue.pop_front();  // 出一个就打印，再把它的左右孩子进队
    l = cur->left;
    r = cur->right;
    // （是否遇到过没有孩子的节点 && （孩子节点是不是叶节点）） || （节点有右节点无左节点）
    if ((left && (l != nullptr || r != nullptr)) || (l == nullptr && r != nullptr)) {
      return false;
    }

    if (l != nullptr) {
      queue.push_back(l);
    }
    if (r != nullptr) {
      queue.push_back(r);
    }
    if (l == nullptr || r == nullptr) {
      left = true;
    }
  }
  return true;
}

// 是否为平衡二叉树
ReturnType* Tree::process(Node* x) {
  if (x == nullptr) {
    return new ReturnType(true, 0);
  }

  ReturnType* leftData = process(x->left);
  ReturnType* rightData = process(x->right);

  int height = max(leftData->height, rightData->height) + 1;  // 当前节点的高度 = 左树或右树的最大高度 + 当前节点的高度1
  // 左树是不是平衡二叉树 && 右树是不是平衡二叉树 && 左树和右树的高度差是不是小于2
  bool isBal = leftData->isBalanced && rightData->isBalanced && abs(leftData->height - rightData->height) < 2;  // 当前节点的树是否平衡
  return new ReturnType(isBal, height);
}
bool Tree::isBalanceTree() {
  return process(head)->isBalanced;
}

// 是否为搜索二叉树
ReturnData* Tree::process_bst(Node* x) {
  if (x == nullptr) {
    return nullptr;
  }
  ReturnData* leftData = process_bst(x->left);
  ReturnData* rightData = process_bst(x->right);

  // 拿到左树和右树的最大值最小值
  int res_min = x->value;
  int res_max = x->value;
  if (leftData != nullptr) {
    res_min = min(res_min, leftData->min);
    res_max = max(res_max, leftData->max);
  }
  if (rightData != nullptr) {
    res_min = min(res_min, rightData->min);
    res_max = max(res_max, rightData->max);
  }

  bool isBST = true;
  // 左树是不是搜索二叉树
  if (leftData != nullptr && (!leftData->isBST || leftData->max >= x->value)) {
    isBST = false;
  }
  // 右树是不是搜索二叉树
  if (rightData != nullptr && (!rightData->isBST || x->value >= rightData->min)) {
    isBST = false;
  }

  return new ReturnData(isBST, res_min, res_max);
}
bool Tree::isSelectTree() {
  return process_bst(head)->isBST;
}

// 是否为满二叉树
ReturnInfo* Tree::process_full(Node* x) {
  if(x == nullptr) {
    return new ReturnInfo(0, 0);
  }

  ReturnInfo* leftData = process_full(x->left);
  ReturnInfo* rightData = process_full(x->right);

  int height = max(leftData->height, rightData->height) + 1;
  int nodes = leftData->nodes + rightData->nodes + 1;
  return new ReturnInfo(height, nodes);
}
bool Tree::isFullTree() {
  ReturnInfo* data = process_full(head);
  return data->nodes == ((1 << data->height) - 1);
}


int main() {
  Tree tree;
  tree.creatTree();
  cout << tree.isFullTree() << endl;
  // tree.printTree(6);
  system("pause");
  return 0;
}