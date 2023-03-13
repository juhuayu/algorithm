#include <iostream>
#include <string>
using namespace std;

class Person {
 public:
  // ------------- 1.成员函数重载 + -------------
  // Person operator+(Person& p) {
  //   Person temp;
  //   temp.m_A = this->m_A + p.m_A;
  //   temp.m_B = this->m_B + p.m_B;
  //   return temp;
  // }
  // ------------- 1.成员函数重载 << -------------
  // 不会利用成员函数重载 << 运算符，因为无法实现 cout 在左侧
  // void operator<<(cout) {
  //   p.operator<<(cout);  ->  p << cout;
  // }
  int m_A;
  int m_B;
};

// ===================================== 加号运算符重载 =====================================
// 运算符重载也可以发生函数重载
// 注意：内置数据类型运算符不可以改变

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
  Person p3 = operator+(p1, p2);
  // 但都可以简写为：
  // Person p3 = p1 + p2;
  cout << "p3.m_A:" << p3.m_A << endl;
  cout << "p3.m_B:" << p3.m_B << endl;

  // 重载运算符
  Person p4 = operator+(p1, 100);
  cout << "p4.m_A:" << p4.m_A << endl;
  cout << "p4.m_B:" << p4.m_B << endl;
}
// ===================================== 左移运算符重载 =====================================
// ------------- 2.全局函数重载 << -------------
// ostream 标准输出流
ostream& operator<<(ostream& cout, Person& p) {
  // 本质： operator<<(cout, p);  ->  cout << p;
  cout << "m_A = " << p.m_A << endl;
  cout << "m_B = " << p.m_B << endl;
  return cout;  // 链式调用，可以使 cout 无限追加
}

void operation_left() {
  Person p1;
  p1.m_A = 10;
  p1.m_B = 20;
  cout << p1 << endl;
}
// ===================================== 递增运算符重载 =====================================
// 前置递增一定要返回自身的引用，后置递增返回值
class MyInt {
  friend ostream& operator<<(ostream& cout, MyInt myint);

 public:
  MyInt() {
    m_Num = 0;
  }
  // 前置 ++ 运算符重载  返回引用是为了一直对一个数据进行递增操作
  MyInt& operator++() {
    m_Num++;
    return *this;  // 将自身返回，链式编程
  }
  // 后置 ++ 运算符重载  int 是占位参数，用来区分前置和后置递增（只能用int）
  MyInt operator++(int) {
    // 先记录，后递增，再返回记录值
    MyInt temp = *this;
    m_Num++;
    return temp;
  }

 private:
  int m_Num;
};
ostream& operator<<(ostream& cout, MyInt myint) {
  cout << myint.m_Num;
  return cout;
}

void operation_add_add() {
  MyInt myint;
  cout << "myInt:" << myint << endl;
  cout << "++(++myInt):" << ++(++myint) << endl;
  cout << "myInt++:" << myint++ << endl;
  cout << "myInt:" << myint << endl;
}

// ===================================== 赋值运算符重载 =====================================
class Member {
 public:
  Member(int age) {
    m_Age = new int(age);
  }
  ~Member() {
    if (m_Age != NULL) {
      delete m_Age;
      m_Age = NULL;
    }
  }
  Member& operator=(Member& m) {  // 返回 Member 的话是返回了一个自生新创建出来的副本
    // 编译器提供的是浅拷贝，在执行析构函数的时候会崩掉，因为释放了同一个地址下的数据
    // m_Age = m.m_Age;
    // 先判断是否有属性在堆区，如果有就先释放干净，然后再深拷贝
    if (m_Age != NULL) {
      delete m_Age;
      m_Age = NULL;
    }
    m_Age = new int(*m.m_Age);
    return *this;
  }
  int* m_Age;
};

void operation_equal() {
  Member m1(24);
  Member m2(18);
  Member m3(31);
  m3 = m2 = m1;
  cout << "m1.age:" << *m1.m_Age << endl;
  cout << "m2.age:" << *m2.m_Age << endl;
  cout << "m3.age:" << *m3.m_Age << endl;
}

// ===================================== 关系运算符重载 =====================================
class Animal {
 public:
  Animal(string name, int age)
      : a_Name(name), a_Age(age) {}
  string a_Name;
  int a_Age;
  // ==
  bool operator==(Animal& a) {
    if (this->a_Age == a.a_Age && this->a_Name == a.a_Name) {
      return true;
    }
    return false;
  }
  // !=
  bool operator!=(Animal& a) {
    if (this->a_Age == a.a_Age && this->a_Name == a.a_Name) {
      return false;
    }
    return true;
  }
};
void operation_relation() {
  Animal a1("Tom", 5);
  Animal a2("Jerry", 4);
  Animal a3("Tom", 5);

  if (a1 == a3) {
    cout << "a1 equal a3" << endl;
  } else {
    cout << "a1 no equal a3" << endl;
  }
  if (a1 != a2) {
    cout << "a1 no equal a2" << endl;
  } else {
    cout << "a1 equal a2" << endl;
  }
}

// ===================================== 函数调用运算符重载 =====================================
// 仿函数
class MyPrint {
  public:
  void operator()(string test) {
    cout << test << endl;
  }
};
class MyAdd {
  public:
  int operator()(int num1, int num2) {
    return num1 + num2;
  }
};

void operation_func() {
  MyPrint myPrint;
  myPrint("hello world");

  MyAdd myAdd;
  cout << myAdd(100, 100) << endl;
  // 匿名函数对象
  cout << MyAdd()(100, 100) << endl;
  
}


int main() {
  operation_add();
  operation_left();
  operation_add_add();
  operation_equal();
  cout << endl;
  operation_relation();
  operation_func();

  system("pause");
  return 0;
}
