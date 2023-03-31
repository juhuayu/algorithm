/*
类模板

类模板与函数模板的区别
1.类模板没有自动类型推导
2.类模板在模板参数列表中可以有默认参数

分文件：将.h和.cpp文件合并，都写在一个文件里，后缀名为.hpp（一般.hpp文件大都是类模板）
一般都是.h写类函数的定义，.cpp文件写类中函数实现，然后使用时包含.h文件
-------------------------------------
普通类中的成员函数一开始就可以创建
类模板中的成员函数在调用时才创建

*/
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

template <class NameType, class AgeType = int>  // 类模板可以写默认参数，函数模板不可以
class Person {
 private:
  /* data */
  NameType m_name;
  AgeType m_age;

 public:
  Person(NameType name, AgeType age)
      : m_name(name), m_age(age){};
  void show() {
    cout << "name: " << m_name << "  age: " << m_age << endl;
  }
  void run(NameType name);
};
template <class NameType, class AgeType>
void Person<NameType,AgeType>::run(NameType name) { // 类模板的成员函数类外实现
    cout << "run!!!" << endl;
}

// --------- 类模板对象做函数参数 ---------
// 指定传入类型（常用）
void printPerson1(Person<string, int>& p) {
  p.show();
}
// 参数模板化（属于类模板配合函数模板）
template <class T1, class T2>
void printPerson2(Person<T1, T2>& p) {
  p.show();
  cout << "T1 type: " << typeid(T1).name() << endl;  // 查看推导出什么类型
  cout << "T2 type: " << typeid(T2).name() << endl;
}
// 整个类模板化（属于类模板配合函数模板）
template <class T>
void printPerson3(T& p) {
  p.show();
  cout << "T type: " << typeid(T).name() << endl;
}

// ================================================================================================
class Animal {
 public:
  void showText() {
    cout << "xxxxxxxxxxxx" << endl;
  }
};
template <class TestType>
class Test {
  TestType test;

 public:
  // 类模板中的成员函数在调用时才创建(所以这个函数只有在调用时TestType没有这个函数会报错),可以编译成功
  void show() {
    test.showText();
  }
};

// ================================================================================================
// 类模板和继承
// 当子类继承父类是一个类模板时，子类再声明的时候，要指定出父类的T类型
// 如果不指定，编译器无法给子类分配内存
// 如果想灵活指定出父类中的T类型，子类也需变成类模板
template <class T>
class Base {
 public:
  T m;
  void showType() {
    cout << "Base T type: " << typeid(T).name() << endl;
  }
};
// class Son: public Base         会报错，没指定父类类型
// class Son: public Base<int>    固定死父类就是int型
template <class T1, class T2>  // T1用来指定son的类型，T2用来指定继承下来的父类的类型
class Son : public Base<T2> {
 public:
  T1 obj;
};

// ================================================================================================
int main() {
  Person<string> p("abc", 10);
  // p.show();
  p.run("xyz");

  printPerson2(p);
  printPerson3(p);

  Test<Animal> t;
  t.show();

  Son<int, char> s;
  s.showType();

  system("pause");
  return 0;
}