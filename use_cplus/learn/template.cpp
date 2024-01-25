/*
函数模板
*/
#include <iostream>
using namespace std;

template <typename T>
void myswap(T& a, T& b) {
  T temp = b;
  b = a;
  a = temp;
}

int main() {
  int a = 1;
  int b = 2;
  myswap(a, b); // 自动类型推导
  cout << "a=" << a << endl;
  cout << "b=" << b << endl;
  myswap<int>(a, b); // 显示指定类型
  cout << "a=" << a << endl;
  cout << "b=" << b << endl;
  system("pause");
  return 0;
}
 