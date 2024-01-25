#include <iostream>
#include <string>

using namespace std;
// 一定注意调用顺序
class Building;
class GayClassOther {
 public:
  GayClassOther();

  void visitYes();
  void visitNo();

  Building* building;
};

class Building {
  friend void GayClassOther::visitYes();

 private:
  string bedRoom;

 public:
  Building();
  string sittingRoom;
};
Building::Building() {
  sittingRoom = "sittingRoom";
  bedRoom = "bedRoom";
};

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
  GayClassOther gco;
  gco.visitYes();
  gco.visitNo();

  system("pause");
  return 0;
}