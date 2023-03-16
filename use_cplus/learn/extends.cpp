/*
class 子类: 继承方式 父类
继承方式有3种：公共，保护，私有
多继承：class 子类: 继承方式 父类, 继承方式 父类, 继承方式 父类

公共：可以访问父类公共和保护，其它不可以访问（父类中的权限完全给子类）
保护：可以访问父类公共和保护，其它不可以访问（父类中的公共权限变成了子类的保护权限）
私有：可以访问父类公共和保护，其它不可以访问（父类中的公共权限变成了子类的私有权限）

父类中的私有权限不管是哪一种继承都访问不到
父类中所有非静态成员属性都会被子类继承下去
父类中私有成员属性是被编译器隐藏了，因此访问不到，但确实被继承下去了

先构造父类，再构造子类，析构的顺序与构造顺序相反

visual studio查看类工具：
1.打开vs的开发人员命令提示符工具
2.跳转到当前类cpp文件所在位置
3.输入：cl /d1 reportSingleClassLayout类名 "类所在的文件名.cpp"
*/
#include <iostream>
#include <string>
using namespace std;

class Animal {
 public:
  string name;
  int age = 18;
  void run() {
    cout << "run!!!" << endl;
  }
};

class Cat : public Animal {
 public:
  void upTree() {
    cout << "cat up tree!" << endl;
  }
  void run() {
    cout << "cat run!!!" << endl;
  }
  int age = 20;
};

class Dog : public Animal {
 public:
  void bite() {
    cout << "dog bite" << endl;
  }
};
// --------------- 菱形继承 ---------------
// 加virtual关键字解决菱形继承相同数据问题（虚继承），Animal类变为虚基类
class Sheep : virtual public Animal {};
class Tuo : virtual public Animal {};
// vbptr 虚基类指针

class SheepTuo : public Sheep, public Tuo {};

int main() {
  Cat cat;
  // 如果子类中出现了和父类同名的成员函数，子类的同名成员会隐藏掉父类中的所有同名成员函数
  cat.run();          // 与父类成员函数同名时，直接调用会优先调子类的函数
  cat.Animal::run();  // 加作用域调父类
  cat.upTree();

  cout << "cat age:" << cat.age << endl;                 // 与父类成员属性同名时，优先子类
  cout << "animal cat age:" << cat.Animal::age << endl;  // 想使用父类的话需要指明

  Dog dog;
  dog.run();
  dog.bite();

  // 当菱形继承两个父类拥有相同的数据，需要加以作用域区分
  SheepTuo st;
  st.Sheep::name = "sheep";
  st.Tuo::name = "tuo";  // 覆盖上面的sheep
  // 这份数据我们知道只有一份就可以，菱形继承导致数据有两份，资源浪费(使用虚继承共享同一份数据)
  cout << "st.Sheep::name = " << st.Sheep::name << endl;  // 打印：tuo
  cout << "st.Tuo::name = " << st.Tuo::name << endl;      // 打印：tuo
  cout << "st.name = " << st.name << endl;                // 打印：tuo

  system("pause");
  return 0;
}
