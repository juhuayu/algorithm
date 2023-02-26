
#include <iostream>
#include <stack>
#include "link_list.cpp"

using namespace std;

// struct List {
//     int val;
//     struct List* next;
// };
// class Node {
//    public:
//     int value;
//     Node *next;
//     Node(int data) {
//         this->value = data;
//     }
// };

int isPalindrome1(Node head) {
    stack<Node> st;
    Node cur = head;
    // while (cur.next != NULL) {
    //     st.push(cur);
    //     cur = cur.next;
    // }
    // while (head != NULL) {
    //     if (head.value != st.pop().value) {
    //         return false
    //     }
    //     head = head.next;
    // }
    return 1;
}

int main() {
  LinkList linkList;
  linkList.CreateLinkList(1);
  linkList.InsertElemAtEnd(2);
  linkList.InsertElemAtEnd(2);
  // cout << isPalindrome1(head) << endl;
  cout << linkList << endl;
  
  system("pause");
  return 0;
}
