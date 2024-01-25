/*
kmp算法
字符串str1和str2，str1是否包含str2，如果包含返回str2在str1中开始的位置
*/

#include <iostream>
#include <string>
using namespace std;
/*
求问号所在位置的next值：
abbstabbecabbstabb?
       ↑           箭头指向的字符（下标为7）在next中的值为2，即前缀=后缀=ab
-------↑         ↑ 问号前一个b的值是7（那么判断问号前一个的字符和该字符串下标为7的字符作比较）即判断箭头所指的字符是否一致，一致则问号所对应的next值为8
--↑              ↑ 假如问号前一个字符不是b，与上述所背，则问号前一个字符与问号前一个字符所对应next中的值7为下标的字符的next中的值2的下一个字符是否一致，即判断箭头所指的字符是否一致

*/
// O(M)
int* getNextArray(string ms) {
  if (ms.length() == 1)
    return new int[1]{-1};
  int* next = new int[ms.length()];
  next[0] = -1;  // 人为规定
  next[1] = 0;   // 人为规定
  int i = 2;     // next数组的位置，从2开始求
  int cn = 0;    // 表示拿哪个字符的位置和i-1位置比，还代表当前使用的信息是多少（长度）
  while (i < ms.length()) {
    if (ms[i - 1] == ms[cn]) {  // 利用前一个字符在next数组求得的值（判断在上一个字符求得的值的下一个字符和上一个字符是否一致，一致的话当前字符在next数组中的值就是上一个字符值+1）
      next[i++] = ++cn; // i++ 该求下一个位置的信息了     ++cn 下一个位置需要使用当前位置的cn值（保持连续性）
    } else if (cn > 0) {
      cn = next[cn];  // 当前跳到cn位置的字符，和i-1位置的字符配不上（next[上一个字符求得的值]）
    } else {
      next[i++] = 0;  // 一路往前跳，都没有相等的
    }
  }
  return next;
}

int getIndexOf(string s, string m) {
  if (m.length() < 1 || s.length() < m.length())
    return -1;
  int i1 = 0;  // 在s中比对的位置
  int i2 = 0;  // 在m中比对的位置
  int* next = getNextArray(m); // O(M)
  // O(N)
  while (i1 < s.length() && i2 < m.length()) {  // i1和i2不越界（i2越界说明有配对成功的，i1越界说明没有匹配到的）
    if (s[i1] == m[i2]) {                       // 比对相等，都向前移动
      i1++;
      i2++;
    } else if (next[i2] == -1) {  // i2已经再不能向前跳了，或者也可以写成 i2==0
      i1++;                       // s字符串换下一个位置和m进行匹配
    } else {
      i2 = next[i2];  // 有前缀和后缀相等的，可以向前跳（相当于m向前推动了next[i2]个距离）
    }
  }
  return i2 == m.length() ? i1 - i2 : -1;
}

// 对str2求最大的小于自身的前缀等于后缀长度

int main() {
  string str1 = "xx123abcxab12xx";
  string str2 = "abc"; // 5

  cout << getIndexOf(str1, str2) << endl;

  system("pause");
  return 0;
}