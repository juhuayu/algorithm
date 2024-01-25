/*
  多态
*/
#include <iostream>
using namespace std;

class Animal {
 public:
  // 虚函数关键字 virtual
  // virtual void speak() { // 加上 virtual 后会有一个指向虚函数表的指针（vfptr）
  //   cout << "animal speak!" << endl;
  // }

  // 可以写为纯虚函数，这时这个类就叫做抽象类
  // 抽象类特点：
  // 1.无法实例化对象
  // 2.子类必须重写抽象类中的纯虚函数，否则也属于抽象类
  virtual void speak() = 0;

  // 有了纯虚析构之后，这个类也属于抽象类，无法实例化对象
  virtual ~Animal() = 0; // 纯虚析构（不加virtual的话析构时不会走子类的析构函数）
};
Animal::~Animal() {
  // 就算是纯虚析构也需要写具体实现，因为父类也可能有数据开辟到堆区
}
// 猫类，继承动物类
class Cat:public Animal {
  void speak() { // 改写父类函数的时候使虚函数指针指向子类的函数
    cout << "cat speak!" << endl;
  }
};
// 狗类，继承动物类
class Dog:public Animal {
  void speak() {
    cout << "dog speak!" << endl;
  }
};
// 执行说话的函数
// 地址早绑定 在编译阶段确定了函数地址
// 如果想执行让猫说话，那么这个地址就不能提前绑定，需要在运行阶段进行绑定，地址晚绑定
// 动态多态需要满足的条件：
// 1.有继承关系
// 2.子类重写父类的虚函数，子类中的 virtual 关键字可写可不写

// 使用：需要父类的指针或者引用去执行子类对象
void doSpeak(Animal &animal) {
  animal.speak(); 
  // 父类加 virtual 关键字打印猫说话，不加打印动物说话
  cout << sizeof(Animal) << endl;
}

int main() {
  Cat cat;
  // 函数参数要求是 Animal ，但可以传继承了这个类的子类，只不过使用的是父类
  doSpeak(cat);

  Dog dog;
  doSpeak(dog);

  // 父类指针在析构的时候，不会调用子类中的析构函数，导致子类如果右堆区属性，会出现内存泄漏
  // 解决：在父类析构函数前加 virtual，变成虚析构
  Animal *anl = new Cat;
  anl->speak();

  system("pause");
  return 0;
}
