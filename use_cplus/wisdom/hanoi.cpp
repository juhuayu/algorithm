/*
  经典汉诺塔问题
*/
#include <iostream>
#include <string>
using namespace std;

// 1~i 圆盘的目标 from -> to ，other是另外一个
void func(int i, string start, string end, string other) {
  if(i == 1) {
    cout << "Move 1 from " << start << " to " << end << endl;
  } else {
    func(i-1, start, other, end);
    cout << "Move "<< i <<" from " << start << " to " << end << endl;
    func(i-1, other, end, start);
  }
}

void hanoi(int n) {
  if(n > 0) {
    func(n, "left", "right", "center");
  }
}

int main() {
  hanoi(3);
  system("pause");
  return 0;
}