#include <iostream>
using namespace std;
 
struct ListNode
{
   int data;
   ListNode *next;
   ListNode(int item) : data(item) { next = NULL; }
};
 
void traversal_List(ListNode* head)
{
   while (head)
   {
      cout << head->data;
      head = head->next;
   }
}
 
ListNode* mergeTwoLists(ListNode* list1, ListNode*list2)
{
   if (list1 == nullptr) return list2;
   if (list2 == nullptr) return list1;
 
   if (list1->data < list2->data)
   {
      list1->next = mergeTwoLists(list1->next, list2);
      return list1;
   }
   else
   {
      list2->next = mergeTwoLists(list1, list2->next);
      return list2;
   }
}
 
int main()
{
   ListNode list1_1(1);
   ListNode list1_2(2);
   ListNode list1_3(4);
 
   ListNode list2_1(1);
   ListNode list2_2(3);
   ListNode list2_3(4);
 
   list1_1.next = &list1_2;
   list1_2.next = &list1_3;
   list1_3.next = NULL;
 
   list2_1.next = &list2_2;
   list2_2.next = &list2_3;
   list2_3.next = NULL;
 
   cout << "list1:";
   traversal_List(&list1_1);
   cout << endl;
   cout << "list2:";
   traversal_List(&list2_1);
   cout << endl;
 
   ListNode* res = mergeTwoLists(&list1_1, &list2_1);
   cout << "new list:"; 
   traversal_List(res);
   cout << endl;
   system("pause");
 
}