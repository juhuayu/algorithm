/*
二叉树的序列化和反序列化
就是内存里的一棵树如何变成字符串形式，又如何字符串形式变成内存里的树
判断一颗二叉树是不是另一颗二叉树的子树
*/

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "CreatTree.cpp"
using namespace std;

void supersplit(const std::string& s, std::vector<std::string>& v, const std::string& c) {
  std::string::size_type pos1, pos2;
  size_t len = s.length();
  pos2 = s.find(c);
  pos1 = 0;
  while (std::string::npos != pos2) {
    v.emplace_back(s.substr(pos1, pos2 - pos1));

    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if (pos1 != len)
    v.emplace_back(s.substr(pos1));
}

class Serialization {
 private:
 public:
  // 层序打印
  void rowOrder(Node* now) {
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
  // 以head为头的树，序列化成字符串返回
  string serialByPre(Node* head) {
    if (head == nullptr) {
      return "#_";
    }
    string res = to_string(head->value) + "_";
    res += serialByPre(head->left);
    res += serialByPre(head->right);
    return res;
  }
  // 反序列化
  Node* reconByPreString(string prestr) {
    vector<std::string> values;
    supersplit(prestr, values, "_");
    list<string> queue;
    for (int i = 0; i != values.size(); i++) {
      queue.push_back(values[i]);
    }
    return reconPreOrder(queue);
  }
  Node* reconPreOrder(list<string>& queue) {
    string value = queue.front();
    queue.pop_front();
    if (value == "#") {
      return nullptr;
    }
    Node* head = new Node(atoi(value.c_str()));
    head->left = reconPreOrder(queue);
    head->right = reconPreOrder(queue);
    return head;
  }
};

int main() {
  CreatTree tree1;
  Node* testTree = tree1.creatTestTree1();

  Serialization serialization;
  string str = serialization.serialByPre(testTree);
  cout << str << endl;

  Node* treeHead = serialization.reconByPreString(str);
  serialization.rowOrder(treeHead);
  system("pause");
  return 0;
}
