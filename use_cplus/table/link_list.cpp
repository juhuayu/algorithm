#include <iostream>
#include <stack>
#include <vector>
using namespace std;

#define Node Node

// 构建一个节点类
class Node {
 public:
  int value;   // 数据域
  Node* next;  // 指针域
};

class LinkList {
 public:
  LinkList();                       // 单链表无参初始化;
  LinkList(int a);                  // 单链表有参初始化;
  ~LinkList();                      // 销毁一个单链表;
  void insertElemAtEnd(int data);   // 在尾部插入指定的元素
  void insertElemAtHead(int data);  // 在头部插入指定元素
  void printLinkList();             // 从头打印单链表

  int isPalindromePlan1();         // 判断是不是回文  时间：O(N) 空间：O(N)
  int isPalindromePlan2();         // 判断是不是回文  时间：O(N) 空间：O(N/2)
  int isPalindromePlan3();         // 判断是不是回文  时间：O(N) 空间：O(1)
  void listPartition1(int pivot);  // 将单链表按某值划分成左边小，中间相等，右边大的形式  时间：O(N) 空间：O(N)
  void listPartition2(int pivot);  // 将单链表按某值划分成左边小，中间相等，右边大的形式  时间：O(N) 空间：O(1)
 private:
  Node* head;                                            // 头结点
  void arrPartition(vector<Node*>& nodeArr, int pivot);  // 单链表转数组以某一个值作划分
  void swap(vector<Node*>& nodeArr, int a, int b);       // 单链表转数组两节点交换
};

// 初始化单链表
LinkList::LinkList() {
  head = new Node;
  head->value = 0;    // 将头结点的数据域定义为0
  head->next = NULL;  // 头结点的下一个定义为NULL
}
// 初始化单链表
LinkList::LinkList(int a) {
  head = new Node;
  head->value = a;    // 将头结点的数据域定义为0
  head->next = NULL;  // 头结点的下一个定义为NULL
}

// 销毁单链表
LinkList::~LinkList() {
  delete head;  // 删除头结点
}

// 在尾部插入指定的元素
void LinkList::insertElemAtEnd(int data) {
  Node* newNode = new Node;  // 定义一个Node结点指针newNode
  newNode->next = NULL;      // 定义newNode的数据域和指针域
  newNode->value = data;
  Node* p = head;      // 定义指针p指向头结点
  if (head == NULL) {  // 当头结点为空时，设置newNode为头结点
    head = newNode;
  } else {  // 循环知道最后一个节点，将newNode放置在最后
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = newNode;
  }
}

// 在头部插入指定元素
void LinkList::insertElemAtHead(int data) {
  Node* newNode = new Node;  // 定义一个Node结点指针newNode
  newNode->value = data;
  Node* p = head;      // 定义指针p指向头结点
  if (head == NULL) {  // 当头结点为空时，设置newNode为头结点
    head = newNode;
  }
  newNode->next = p->next;  // 将新节点插入到指定位置
  p->next = newNode;
}

// 从头打印单链表
void LinkList::printLinkList() {
  Node* cur = head;
  while (cur != NULL) {
    cout << cur->value << "--";
    cur = cur->next;
  }
}

// 该单链表是否为回文  时间：O(N) 空间：O(N)
int LinkList::isPalindromePlan1() {
  stack<Node*> st;  // 创建一个栈
  Node* cur = head;
  while (cur != NULL) {  // 将列表所有节点放入栈
    st.push(cur);
    cur = cur->next;
  }
  cur = head;
  while (cur != NULL) {
    if (cur->value != st.top()->value) {  // 判断栈顶与遍历到的列表节点是否相等
      return 0;
    }
    st.pop();         // 说明相等，栈顶弹出一个
    cur = cur->next;  // 指针指向下一个节点
  }
  return 1;
}

// 该单链表是否为回文  时间：O(N) 空间：O(N/2)
int LinkList::isPalindromePlan2() {
  Node* right = head->next;
  Node* cur = head;                                       // 定义快慢指针
  while (cur->next != NULL && cur->next->next != NULL) {  // 慢指针走到一半
    right = right->next;
    cur = cur->next->next;
  }
  stack<Node*> st;         // 创建一个栈
  while (right != NULL) {  // 后一半的放到栈里
    st.push(right);
    right = right->next;
  }
  cur = head;
  while (!st.empty()) {  // 比对的过程和方法一一致
    if (cur->value != st.top()->value) {
      return 0;
    }
    st.pop();
    cur = cur->next;
  }
  return 1;
}

// 该单链表是否为回文  时间：O(N) 空间：O(1)
int LinkList::isPalindromePlan3() {
  Node* n1 = head;
  Node* n2 = head;                                      // 定义快慢指针
  while (n2->next != NULL && n2->next->next != NULL) {  // 慢指针走到一半
    n1 = n1->next;
    n2 = n2->next->next;
  }
  n2 = n1->next;
  n1->next = NULL;
  Node* n3 = NULL;
  while (n2 != NULL) {  // 右半部分逆序，都连到中点
    n3 = n2->next;
    n2->next = n1;
    n1 = n2;
    n2 = n3;
  }
  n3 = n1;
  n2 = head;
  int res = 1;
  while (n1 != NULL && n2 != NULL) {  // 左右都往中间走作比较
    if (n1->value != n2->value) {
      res = 0;
      break;
    }
    n1 = n1->next;
    n2 = n2->next;
  }
  n1 = n3->next;
  n3->next = NULL;
  while (n1 != NULL) {  // 右半部分再逆序回去
    n2 = n1->next;
    n1->next = n3;
    n3 = n1;
    n1 = n2;
  }
  return res;
}

// 将单链表按某值划分成左边小，中间相等，右边大的形式  时间：O(N) 空间：O(N)
void LinkList::listPartition1(int pivot) {
  if (head == NULL) {
    return;
  }
  Node* cur = head;
  int i = 0;
  while (cur != NULL) {
    i++;
    cur = cur->next;
  }
  vector<Node*> nodeArr(i);
  i = 0;
  cur = head;
  for (i = 0; i != nodeArr.size(); i++) {
    nodeArr[i] = cur;
    cur = cur->next;
  }
  arrPartition(nodeArr, pivot);
  for (i = 1; i != nodeArr.size(); i++) {
    nodeArr[i - 1]->next = nodeArr[i];
  }
  nodeArr[i - 1]->next = NULL;
  head = nodeArr[0];
}
// 单链表转数组以某一个值作划分
void LinkList::arrPartition(vector<Node*>& nodeArr, int pivot) {
  int small = -1;
  int big = nodeArr.size();
  int index = 0;
  while (index != big) {
    if (nodeArr[index]->value < pivot) {
      swap(nodeArr, ++small, index++);
    } else if (nodeArr[index]->value > pivot) {
      swap(nodeArr, --big, index);
    } else {
      index++;
    }
  }
}
// 单链表转数组两节点交换
void LinkList::swap(vector<Node*>& nodeArr, int a, int b) {
  Node* temp = nodeArr[a];
  nodeArr[a] = nodeArr[b];
  nodeArr[b] = temp;
}
// 将单链表按某值划分成左边小，中间相等，右边大的形式  时间：O(N) 空间：O(1)
void LinkList::listPartition2(int pivot) {
  Node* sH = NULL;    // 小于头 small head
  Node* sT = NULL;    // 小于尾 small tail
  Node* eH = NULL;    // 等于头 equal head
  Node* eT = NULL;    // 等于尾 equal tail
  Node* mH = NULL;    // 大于头 big head
  Node* mT = NULL;    // 大于尾 big tail
  Node* next = NULL;  // save next node
  Node* cur = head;
  while (cur != NULL) {
    next = cur->next;
    cur->next = NULL;
    if (cur->value < pivot) { // 小于划分值
      if (sH == NULL) {
        sH = cur;
        sT = cur;
      } else {
        sT->next = cur;
        sT = cur;
      }
    } else if (cur->value == pivot) { // 等于划分值
      if (eH == NULL) {
        eH = cur;
        eT = cur;
      } else {
        eT->next = cur;
        eT = cur;
      }
    } else { // 大于划分值
      if (mH == NULL) {
        mH = cur;
        mT = cur;
      } else {
        mT->next = cur;
        mT = cur;
      }
    }
    cur = next;
  }
  // 把小于区等于区大于区重连
  if (sT != NULL) { // 如果有小于区
    sT->next = eH;
    eT = eT == NULL ? sT : eT; // 下一步，谁去连大于区域的头，谁就变成eT
  }
  if (eT != NULL) {
    eT->next = mH;
  }
  head = sH != NULL ? sH : (eH != NULL ? eH : mH);
}

int main() {
  LinkList linkList(1);
  linkList.insertElemAtEnd(4);
  linkList.insertElemAtEnd(3);
  linkList.insertElemAtEnd(2);
  linkList.insertElemAtEnd(7);
  linkList.insertElemAtEnd(2);
  linkList.insertElemAtEnd(4);
  linkList.insertElemAtEnd(9);
  // cout << linkList.isPalindromePlan3() << endl;
  linkList.listPartition2(4);
  linkList.printLinkList();
  system("pause");
  return 0;
}
