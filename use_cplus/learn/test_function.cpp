/*
测试函数的实现

好用的测试函数框架  ->  google test
*/

#include <iostream>
using namespace std;

typedef struct
{
  int output;
  int a;
  int b;
  int (*testFunc)(int, int);
} T_testFunc;

T_testFunc* addFunc(int (*testFunc)(int, int), int a, int b, int output) {
  T_testFunc *m_test = (T_testFunc *)malloc(sizeof(T_testFunc));
  m_test->a = a;
  m_test->b = b;
  m_test->testFunc = testFunc;
  m_test->output = output;
  return m_test;
}

void runTest(T_testFunc *p_test) {
  if (p_test != NULL)
  {
    int count = p_test->testFunc(p_test->a, p_test->b);
    if (count == p_test->output)
    {
      cout << "success" <<endl;
    } else {
      cout << "fail" << count << "!=" << p_test->output << endl;
    }
    free(p_test);
  }
}

int add(int a, int b) {
  return a+b;
}

int main() {
  T_testFunc *m_test = addFunc(add, 1, 2, 3);
  runTest(m_test);

  system("pause");
  return 0;
}
