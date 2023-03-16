/*
获取中序遍历中的后继节点
*/

#include <iostream>
#include "CreatTree.cpp"
using namespace std;

class SuccessorNode {
 private:
  PNode* getLeftMost(PNode* node);

 public:
  PNode* getSuccessorNode(PNode* node);
};

PNode* SuccessorNode::getSuccessorNode(PNode* node) {
  if (node == nullptr)
    return node;
  if (node->right != nullptr) {
    return getLeftMost(node->right); // 获取右子树上的最左节点
  } else {
    // 无右子树则向上找第一个是左孩子的节点的父节点
    PNode* parent = node->parent;
    // 向上找第一个是左孩子的节点（node）
    while (parent != nullptr && parent->left != node) {
      node = parent;
      parent = node->parent;
    }
    // 返回父节点
    return parent;
  }
}

PNode* SuccessorNode::getLeftMost(PNode* node) {
  if(node == nullptr) return node;
  while (node->left != nullptr)
  {
    node = node->left;
  }
  return node;
}

int main() {
  CreatTree tree1;
  ReturnType_SON* testTree = tree1.creatParentTree();

  SuccessorNode sn;
  PNode* res = sn.getSuccessorNode(testTree->o1);
  cout << res->value << endl;
  
  system("pause");
  return 0;
}