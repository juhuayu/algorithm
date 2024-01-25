/*
二叉树的中序遍历

给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。
*/

/*
Definition for a binary tree node.
*/
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <stack>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
  vector<int> inorderTraversal(TreeNode* root) {
      vector<int> res;
      inOrderRecur(root, res);
      return res;
  }

  void inOrderRecur(TreeNode* node, vector<int> &res) {
      if(node == nullptr) {
          return;
      }
      inOrderRecur(node -> left, res);
      res.push_back(node ->val);
      inOrderRecur(node -> right, res);
  }

  vector<int> inorderTraversal(TreeNode* root) {
    stack<TreeNode*> st;
    vector<int> res;
    st.push(root);
    while(!st.empty()) {
      TreeNode* tmp = st.top();
      st.pop();
      if(tmp != nullptr) {
        st.push(tmp -> right);
        st.push(tmp);
        st.push(tmp -> left);
      } else {
        if(!st.empty()) {
          res.push_back(st.top() -> val);
          st.pop();
        }
      }
    }
    return res;
  }
};

