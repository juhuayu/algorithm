#include <iostream>
#include <stack>
using namespace std;

/*
给你一个栈，请你逆序这个栈，不能申请额外的数据结构，只能使用递归函数
如何实现?
*/

// 取栈中最下面的元素，其余的不变
int f(stack<int> &st) {
  int result = st.top();
  st.pop();
  if(st.empty()) {
    return result;
  } else {
    int last = f(st);
    st.push(result);
    return last;
  }
}

void reverse(stack<int> &st) {
  if(st.empty()) {
    return;
  }
  int i = f(st);
  reverse(st);
  st.push(i);
}

int main() {
  stack<int> st;
  st.push(1);
  st.push(2);
  st.push(3);

  reverse(st);

  while(!st.empty()) {
    cout << st.top() << "-";
    st.pop();
  }

  system("pause");
  return 0;
}