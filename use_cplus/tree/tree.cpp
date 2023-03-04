#include <iostream>
#include <stack>
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

 public:
  Tree();
  ~Tree();
  void creatTree();
  void printTree(int i);
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
  tree.printTree(3);
  tree.printTree(6);
  system("pause");
  return 0;
}