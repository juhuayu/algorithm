#include <iostream>
#include <string>

using namespace std;

class Building;
// 有个坑：构造函数写在类里面的话会出现编译顺序上的错误，见 friend_classify_keng.cpp 文件
// ---------------------------- 类内成员访问其它类内的私有成员 ----------------------------
// 成员函数做友元
class GayClassOther {
 public:
  Building* building;
  GayClassOther();
  void visitYes();
  void visitNo();
};
// ---------------------------------------- 主要 ----------------------------------------
class Building {
  friend void goodGay(Building* b);       // 添加这个全局函数为友元
  friend class GayClass;                  //  使 GayClass 这个类成为该类的好朋友，可以访问私有成员
  friend void GayClassOther::visitYes();  //  使 GayClassOther 这个类下的 visitYes 成为该类的好朋友，可以访问私有成员
 private:
  string bedRoom;

 public:
  Building();
  string sittingRoom;
};
Building::Building() {
  this->sittingRoom = "sittingRoom";
  this->bedRoom = "bedRoom";
};

// ------------------------------ 全局函数访问类内的私有成员 ------------------------------
// 全局函数做友元
void goodGay(Building* b) {
  cout << "can can need:" << b->sittingRoom << endl;
  cout << "can can need:" << b->bedRoom << endl;  // 正常访问不了私有下的内容
}
// ------------------------------- 类访问其它类内的私有成员 -------------------------------
// 类做友元
class GayClass {
 public:
  Building* building;
  GayClass() {
    building = new Building();
  }
  void visit() {  // 参观函数，访问building中的属性
    cout << "can can need by class:" << building->sittingRoom << endl;
    cout << "can can need by class:" << building->bedRoom << endl;  // 正常访问不了私有下的内容
  }
};
// ---------------------------- 类内成员访问其它类内的私有成员 ----------------------------
// 成员函数做友元
GayClassOther::GayClassOther() {
  building = new Building();
}
void GayClassOther::visitYes() {
  cout << "can can need by class other yes:" << building->sittingRoom << endl;
  cout << "can can need by class other yes:" << building->bedRoom << endl;
}
void GayClassOther::visitNo() {
  cout << "can can need by class other yes:" << building->sittingRoom << endl;
}

int main() {
  Building building;
  goodGay(&building);

  GayClass goodGay;
  goodGay.visit();

  GayClassOther gco;
  gco.visitYes();
  gco.visitNo();

  system("pause");
  return 0;
}