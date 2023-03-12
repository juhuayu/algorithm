#include <iostream>
using namespace std;

// 加号运算符重载
// 运算符重载也可以发生函数重载
// 注意：内置数据类型运算符不可以改变

class Person {
 public:
  // ------------- 1.成员函数重载 + -------------
  // Person operator+(Person& p) {
  //   Person temp;
  //   temp.m_A = this->m_A + p.m_A;
  //   temp.m_B = this->m_B + p.m_B;
  //   return temp;
  // }
  int m_A;
  int m_B;
};

// ------------- 2.全局函数重载 + -------------
Person operator+(Person& p1, Person& p2) {
  Person temp;
  temp.m_A = p1.m_A + p2.m_A;
  temp.m_B = p1.m_B + p2.m_B;
  return temp;
}
Person operator+(Person& p1, int num) {
  Person temp;
  temp.m_A = p1.m_A + num;
  temp.m_B = p1.m_B + num;
  return temp;
}


void operation_add() {
  Person p1;
  p1.m_A = 10;
  p1.m_B = 20;
  Person p2;
  p2.m_A = 30;
  p2.m_B = 40;
  // 成员函数本质调用：
  // Person p3 = p1.operator+(p2);
  // 全局函数本质调用：
  Person p3 = operator+(p1,p2);
  // 但都可以简写为：
  // Person p3 = p1 + p2;
  cout << "p3.m_A:" << p3.m_A << endl;
  cout << "p3.m_B:" << p3.m_B << endl;

  // 重载运算符
  Person p4 = operator+(p1,100);
  cout << "p4.m_A:" << p4.m_A << endl;
  cout << "p4.m_B:" << p4.m_B << endl;
}

int main() {
  operation_add();

  system("pause");
  return 0;
}
