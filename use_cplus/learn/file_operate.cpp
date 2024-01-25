#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void test() {
  ofstream ofs;
  ofs.open("file_operate.txt", ios::out);
  ofs << "hello" << endl;
  ofs.close();

  // 读文件
  ifstream ifs;
  ifs.open("file_operate.txt", ios::in);
  if (!ifs.is_open()) {
    cout << "file open error" << endl;
    return;
  }
  // 第一种
  char buf[1024] = {0};
  while (ifs >> buf) {
    cout << buf << endl;
  }
  // 第二种
  while (ifs.getline(buf, sizeof(buf))) {
    cout << buf << endl;
  }
  // 第三种
  string bufstr;
  while (getline(ifs, bufstr)) {
    cout << bufstr << endl;
  }
  // 第四种 EOF (end of file)
  char c;
  while ((c = ifs.get()) != EOF) {
    cout << c;
  }

  ifs.close();
}

class Person {
 public:
  char m_Name[64];
  int m_age;
};
// 二进制读写
void write_bin() {
  ofstream ofs("file_operate_bin.txt", ios::out | ios::binary);  // 使用构造
  // ofs.open("file_operate_bin.txt", ios::out | ios::binary);
  Person p = {"zhang san", 18};
  ofs.write((const char*)&p, sizeof(Person));
  ofs.close();

  ifstream ifs;
  ifs.open("file_operate_bin.txt", ios::in | ios::binary);
  if (!ifs.is_open()) {
    cout << "file open error" << endl;
    return;
  }
  Person pr;
  ifs.read((char *)&pr, sizeof(Person));
  ifs.close();
  cout << pr.m_Name << endl;
  cout << pr.m_age << endl;
}

int main() {
  // test();
  write_bin();
  system("pause");
  return 0;
}
