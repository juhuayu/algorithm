#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

class Node {
 public:
  Node() {
    value = 0;
    next = NULL;
    rand = NULL;
  }
  Node(int val) {
    value = val;
    next = NULL;
    rand = NULL;
  }
  int value;   // 数据域
  Node* next;  // 指针域
  Node* rand;  // 随机指针域
};

class LinkList {
 public:
  LinkList() {
    newHead = new Node;
    head = new Node;
    Node* n1;
    Node* n2;

    head->value = 1;
    head->next = n1;
    head->rand = n2;

    n1->value = 2;
    n1->next = n2;
    n1->rand = head;

    n2->value = 3;
    n2->next = NULL;
    n2->rand = NULL;
  }

  // 带有随机指针的列表复制 使用哈希表（此时头节点应该是n1）
  void copyListWithRand1() {
    unordered_map<Node*, Node*> map;
    Node* cur = head;
    while (cur != NULL) {
      map.insert(pair<Node*, Node*>(cur, new Node(cur->value)));
      cur = cur->next;
    }
    cur = head;
    while (cur != NULL) {
      map.at(cur)->next = cur->next == NULL ? NULL : map.at(cur->next);
      map.at(cur)->rand = cur->rand == NULL ? NULL : map.at(cur->rand);
      cur = cur->next;
    }
    newHead = map.at(head);
  }

  // 带有随机指针的列表复制（新列表 rand 方向上有点问题）
  void copyListWithRand2() {
    Node* cur = head;
    Node* next = NULL;

    while (cur != NULL) {
      next = cur->next;
      cur->next = new Node(cur->value); // 当前节点的下一个放它的克隆节点
      cur->next->next = next;
      cur = next;
    }
    cur = head;
    Node* curCopy = NULL;

    while(cur != NULL) {
      next = cur->next->next;
      curCopy = cur->next;
      curCopy->rand = cur->rand != NULL? cur->next->next : NULL; // 只需要关心 rand 指针的连接
      cur = next;
    }
    Node* res = head->next;
    cur = head;
    while (cur != NULL) { // 将克隆列表分离出来
      next = cur->next->next;
      curCopy = cur->next;
      cur->next = next;
      curCopy->next = next != NULL? next->next : NULL;
      cur = next;
    }
    newHead = res;
  }

  // 打印老列表
  void printOldLinkList() {
    if (head == NULL)
      return;
    cout << "old linklist at next:" << endl;
    Node* temp = head;
    while (temp != NULL) {
      cout << temp->value << "---";
      temp = temp->next;
    }
    cout << endl;
    cout << "old linklist at rand:" << endl;
    temp = head;
    while (temp != NULL) {
      cout << temp->value << "---";
      temp = temp->rand;
    }
    cout << endl;
  }
  // 打印复制的列表
  void printNewLinkList() {
    if (newHead == NULL) {
      cout << "empty!" << endl;
      return;
    }
    cout << "new linklist at next:" << endl;
    Node* temp = newHead;
    while (temp != NULL) {
      cout << temp->value << "---";
      temp = temp->next;
    }
    cout << endl;
    cout << "new linklist at rand:" << endl;
    temp = newHead;
    while (temp != NULL) {
      cout << temp->value << "---";
      temp = temp->rand;
    }
    cout << endl;
  }

 private:
  Node* head;
  Node* newHead;
};

int main() {
  LinkList linkList;
  linkList.copyListWithRand2();
  linkList.printOldLinkList();
  linkList.printNewLinkList();

  system("pause");
  return 0;
}