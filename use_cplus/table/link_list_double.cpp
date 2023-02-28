#include <iostream>
using namespace std;

// 构建一个节点类
class Node {
 public:
  int value;   // 数据域
  Node* next;  // 指针域
};

class LinkListDouble {
 private:
  Node* head1;
  Node* head2;
  Node* getLoopNode(int i);                  // 找到链表的第一个入环节点，无环返回null
  Node* noLoop();                            // 两个链表都无环，返回第一个相交节点，不相交返回NULL
  Node* bothLoop(Node* loop1, Node* loop2);  // 两个有环链表，返回第一个相交节点，不相交返回NULL

 public:
  LinkListDouble();
  ~LinkListDouble();

  void creatIntersect(int len1, int len2, int intersect);  // 创建链表1长度为len1，链表2长度len2，倒数第intersect位置相交
  void printLinkList(int count);                           // 打印第几个链表

  Node* getIntersectNode();  // 获取两条单链表相交的节点
};

LinkListDouble::LinkListDouble() {
  head1 = new Node;
  head1->value = 0;
  head1->next = NULL;

  head2 = new Node;
  head2->value = 0;
  head2->next = NULL;
}

LinkListDouble::~LinkListDouble() {
  delete head1;
  delete head2;
}
// 链表1长度为len1，链表2长度len2，倒数第intersect位置相交
void LinkListDouble::creatIntersect(int len1, int len2, int intersect) {
  if (len1 < intersect || len2 < intersect) {
    cout << "no!" << endl;
    return;
  }
  // 第一个链表
  Node* temp1 = NULL;
  for (int i = 1; i <= len1 - intersect; i++) {
    Node* newNode = new Node;
    newNode->value = i;
    newNode->next = NULL;
    if (temp1 == NULL) {
      head1->next = newNode;
    } else {
      temp1->next = newNode;
    }
    temp1 = newNode;
  }
  // 第二个链表
  Node* temp2 = NULL;
  for (int i = 1; i <= len2 - intersect; i++) {
    Node* newNode = new Node;
    newNode->value = i;
    newNode->next = NULL;
    if (temp2 == NULL) {
      head2->next = newNode;
    } else {
      temp2->next = newNode;
    }
    temp2 = newNode;
  }
  // 公共结尾部分
  Node* temp = NULL;  // 相交节点
  for (int i = 10; i <= intersect + 10; i++) {
    Node* newNode = new Node;
    newNode->value = i;
    newNode->next = NULL;
    if (temp == NULL) {
      temp1->next = newNode;
      temp2->next = newNode;
    } else {
      temp->next = newNode;
    }
    temp = newNode;
  }
}

void LinkListDouble::printLinkList(int count) {
  Node* cur = NULL;
  switch (count) {
    case 1:
      cur = head1;
      break;
    case 2:
      cur = head2;
      break;
    default: {
      cout << "no!" << endl;
      return;
    } break;
  }
  cout << "linklist" << count << ": ";
  while (cur != NULL) {
    cout << cur->value << "-";
    cur = cur->next;
  }
  cout << endl;
}

Node* LinkListDouble::getIntersectNode() {
  if (head1 == NULL || head2 == NULL) {
    return NULL;
  }
  Node* loop1 = getLoopNode(1);
  Node* loop2 = getLoopNode(2);
  if (loop1 == NULL && loop2 == NULL) {
    return noLoop();
  }
  if (loop1 != NULL && loop2 != NULL) {
    return bothLoop(loop1, loop2);
  }
  return NULL;
}

// 找到链表的第一个入环节点，无环返回null
Node* LinkListDouble::getLoopNode(int i) {
  Node* n1 = NULL;
  Node* n2 = NULL;  // 定义快慢指针
  if (i == 1) {
    if (head1 == NULL || head1->next == NULL || head1->next->next == NULL)
      return NULL;
    n1 = head1->next;
    n2 = head1->next->next;  // 定义快慢指针
  } else {
    if (head2 == NULL || head2->next == NULL || head2->next->next == NULL)
      return NULL;
    n1 = head2->next;
    n2 = head2->next->next;  // 定义快慢指针
  }

  while (n1 != n2) {  // 有环的话第一次相遇一定在环上
    if (n2->next == NULL || n2->next->next == NULL) {
      return NULL;
    }
    n2 = n2->next->next;
    n1 = n1->next;
  }
  if(i == 1) { // 快指针回到头部
    n2 = head1;
  } else {
    n2 = head2;
  }
  while (n1 != n2) {  // 两个指针每次都走一步，再次相遇一定在入环节点位置
    n1 = n1->next;
    n2 = n2->next;
  }
  return n1;
}
// 两个链表都无环，返回第一个相交节点，不相交返回NULL
Node* LinkListDouble::noLoop() {
  if (head1 == NULL || head2 == NULL) {
    return NULL;
  }
  Node* cur1 = head1;
  Node* cur2 = head2;
  int n = 0;
  while (cur1->next != NULL) {
    n++;
    cur1 = cur1->next;
  }
  while (cur2->next != NULL) {
    n--;
    cur2 = cur2->next;
  }
  if (cur1 != cur2) {  // 相交的话最后一个节点一定是同一个
    return NULL;
  }
  // n: 链表1长度-链表2长度的值
  cur1 = n > 0 ? head1 : head2;          // 谁长，谁的头变成head1
  cur2 = cur1 == head1 ? head2 : head1;  // 谁短，谁的头变成head2

  n = abs(n);
  while (n != 0) {  // 长链表走差之步
    n--;
    cur1 = cur1->next;
  }
  while (cur1 != cur2) {  // 相等的时候就是相交的节点
    cur1 = cur1->next;
    cur2 = cur2->next;
  }
  return cur1;
}
// 两个有环链表，返回第一个相交节点，不相交返回NULL
Node* LinkListDouble::bothLoop(Node* loop1, Node* loop2) {
  Node* cur1 = NULL;
  Node* cur2 = NULL;
  if (loop1 == loop2) {  // 入环节点相同，这时与有没有环没关系，与无环找交点类似
    cur1 = head1;
    cur2 = head2;
    int n = 0;
    while (cur1 != loop1) {
      n++;
      cur1 = cur1->next;
    }
    while (cur2 != loop2) {
      n--;
      cur2 = cur2->next;
    }
    cur1 = n > 0 ? head1 : head2;          // 谁长，谁的头变成head1
    cur2 = cur1 == head1 ? head2 : head1;  // 谁短，谁的头变成head2
    n = abs(n);
    while (n != 0) {  // 长链表走差之步
      n--;
      cur1 = cur1->next;
    }
    while (cur1 != cur2) {
      cur1 = cur1->next;
      cur2 = cur2->next;
    }
    return cur1;
  } else {
    // 链表1与链表2相交的节点在环上
    cur1 = loop1->next;
    while (cur1 != loop1) {
      if (cur1 == loop2) {  // 在链表1的环上找链表2入环的节点
        return loop1;
      }
      cur1 = cur1->next;
    }
    return NULL;
  }
}

int main() {
  LinkListDouble linkList;
  linkList.creatIntersect(6, 9, 3);

  linkList.printLinkList(1);
  linkList.printLinkList(2);

  Node* res = linkList.getIntersectNode();
  cout << "intersect node value:" << res->value << endl;

  system("pause");
  return 0;
}