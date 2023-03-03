/**
 * 将两个升序链表合并为一个新的 升序 链表并返回。
 * 新链表是通过拼接给定的两个链表的所有节点组成的。
 *
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 *
 */

#include <iostream>
using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution
{
public:
  // 第一个思路，不会改变原指针方向 内存14.6M
  ListNode *mergeTwoLists1(ListNode *list1, ListNode *list2)
  {
    ListNode *cur = new ListNode();
    ListNode *cur_l = cur;
    ListNode *l1 = list1;
    ListNode *l2 = list2;
    while (l1 != nullptr && l2 != nullptr)
    {
      if (l1->val <= l2->val)
      {
        cur_l->next = new ListNode(l1->val);
        l1 = l1->next;
      }
      else
      {
        cur_l->next = new ListNode(l2->val);
        l2 = l2->next;
      }
      cur_l = cur_l->next;
    }
    while (l1 != nullptr)
    {
      cur_l->next = new ListNode(l1->val);
      l1 = l1->next;
      cur_l = cur_l->next;
    }
    while (l2 != nullptr)
    {
      cur_l->next = new ListNode(l2->val);
      l2 = l2->next;
      cur_l = cur_l->next;
    }
    return cur->next;
  }
  // 比第一个内存使用小了一点点  内存14.4M
  ListNode *mergeTwoLists2(ListNode *list1, ListNode *list2)
  {
    ListNode *cur = new ListNode();
    ListNode *cur_l = cur;
    while (list1 != nullptr && list2 != nullptr)
    {
      cur_l->next = list1->val < list2->val ? list1 : list2;
      list1->val < list2->val ? list1 = list1->next : list2 = list2->next;
      cur_l = cur_l->next;
    }
    while (list1 != nullptr)
    {
      cur_l->next = list1;
      list1 = list1->next;
      cur_l = cur_l->next;
    }
    while (list2 != nullptr)
    {
      cur_l->next = list2;
      list2 = list2->next;
      cur_l = cur_l->next;
    }
    return cur->next;
  }
  // 力扣题解，是真nb  内存14.3M
  ListNode *mergeTwoLists3(ListNode *list1, ListNode *list2)
  {
    ListNode *dummy = new ListNode(0);
    ListNode *cur = dummy;
    while (list1 != nullptr && list2 != nullptr)
    {
      ListNode **pp = (list1->val < list2->val) ? &list1 : &list2;
      cur->next = *pp;
      cur = cur->next;
      *pp = (*pp)->next;
    }
    cur->next = (list1 == nullptr) ? list2 : list1;

    ListNode *ans = dummy->next;
    delete dummy;
    return ans;
  }

  void printList(ListNode *head)
  {
    ListNode *cur = head;
    while (cur != nullptr)
    {
      cout << cur->val << '-';
      cur = cur->next;
    }
    cout << endl;
  }
};

int main()
{
  Solution solution;
  ListNode *l1_n3 = new ListNode(4);
  ListNode *l1_n2 = new ListNode(2, l1_n3);
  ListNode *l1_n1 = new ListNode(1, l1_n2);

  ListNode *l2_n3 = new ListNode(4);
  ListNode *l2_n2 = new ListNode(3, l2_n3);
  ListNode *l2_n1 = new ListNode(1, l2_n2);

  // ListNode *res = solution.mergeTwoLists1(l1_n1, l2_n1);
  ListNode *res = solution.mergeTwoLists3(l1_n1, l2_n1);
  solution.printList(l1_n1);
  solution.printList(l2_n1);
  solution.printList(res);
  system("pause");
  return 0;
}