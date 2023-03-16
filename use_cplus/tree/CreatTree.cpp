#include <iostream>
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
class PNode {
 public:
  int value;      // 数据
  PNode* left;    // 左节点
  PNode* right;   // 右节点
  PNode* parent;  // 父节点
  PNode()
      : value(0), left(nullptr), right(nullptr), parent(nullptr) {}
  PNode(int i)
      : value(i), left(nullptr), right(nullptr), parent(nullptr) {}
  PNode(int i, PNode* l, PNode* r)
      : value(i), left(l), right(r), parent(nullptr) {}
  PNode(int i, PNode* l, PNode* r, PNode* p)
      : value(i), left(l), right(r), parent(p) {}
};
// ReturnType_文件名缩写
class ReturnType_LCA {
 public:
  Node* head;
  Node* o1;
  Node* o2;
  ReturnType_LCA(Node* h, Node* a, Node* b)
      : head(h), o1(a), o2(b){};
};
class ReturnType_SON {
 public:
  PNode* head;
  PNode* o1;
  ReturnType_SON(PNode* h, PNode* a)
      : head(h), o1(a){};
};

class CreatTree {
 public:
  CreatTree();
  ~CreatTree();

  Node* creatTestTree1();
  Node* creatTestTree2();
  Node* creatTestTree3();
  ReturnType_LCA* creatTestTree_lca();
  ReturnType_SON* creatParentTree();
};

CreatTree::CreatTree() {
}

CreatTree::~CreatTree() {
}

Node* CreatTree::creatTestTree1() {
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
  Node* n1 = new Node(1, n2, n3);
  return n1;
}

Node* CreatTree::creatTestTree2() {
  /*
              1
            /   \
           2     3
          / \   /
         4   5 6
            /   \
           7     8
          /
         9
  */
  Node* n9 = new Node(9);
  Node* n8 = new Node(8);
  Node* n7 = new Node(7);
  n7->left = n9;
  Node* n6 = new Node(6);
  n6->right = n8;
  Node* n5 = new Node(5);
  n5->left = n7;
  Node* n4 = new Node(4);
  Node* n3 = new Node(3);
  n3->left = n6;
  Node* n2 = new Node(2, n4, n5);
  Node* n1 = new Node(1, n2, n3);
  return n1;
}

Node* CreatTree::creatTestTree3() {
  /*
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
  */
  Node* n7 = new Node(7);
  Node* n6 = new Node(6);
  Node* n5 = new Node(5);
  Node* n4 = new Node(4);
  Node* n3 = new Node(3, n6, n7);
  Node* n2 = new Node(2, n4, n5);
  Node* n1 = new Node(1, n2, n3);
  return n1;
}

ReturnType_LCA* CreatTree::creatTestTree_lca() {
  /*
              1
            /   \
           2     3
          / \   /
         4   5 6
            /   \
           7     8
          /
         9
  */
  Node* n9 = new Node(9);
  Node* n8 = new Node(8);
  Node* n7 = new Node(7);
  n7->left = n9;
  Node* n6 = new Node(6);
  n6->right = n8;
  Node* n5 = new Node(5);
  n5->left = n7;
  Node* n4 = new Node(4);
  Node* n3 = new Node(3);
  n3->left = n6;
  Node* n2 = new Node(2, n4, n5);
  Node* n1 = new Node(1, n2, n3);
  return new ReturnType_LCA(n1, n9, n4);
}

ReturnType_SON* CreatTree::creatParentTree() {
  /*
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
            /   \
           8     9
  */
  PNode* n9 = new PNode(9);
  PNode* n8 = new PNode(8);
  PNode* n7 = new PNode(7);
  PNode* n6 = new PNode(6);
  n6->right = n9;
  PNode* n5 = new PNode(5);
  n5->left = n8;
  PNode* n4 = new PNode(4);
  PNode* n3 = new PNode(3, n6, n7);
  PNode* n2 = new PNode(2, n4, n5);
  PNode* n1 = new PNode(1, n2, n3);

  n9->parent = n6;
  n8->parent = n5;
  n7->parent = n3;
  n6->parent = n3;
  n5->parent = n2;
  n4->parent = n2;
  n3->parent = n1;
  n2->parent = n1;
  return new ReturnType_SON(n1, n5);
}