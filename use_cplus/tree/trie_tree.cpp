/*
前缀树（经典）
*/

#include <iostream>
using namespace std;
// 26 个小写英文字母
#define NUMBER 26

// 节点的结构
class TrieNode {
 public:
  int pass;
  int end;
  // 如果字符很多的话，数组很浪费空间
  // 优化：使用哈希表 unordered_map<char,Node> char代表有到这个字符的路，Node是走到下级的那个节点
  TrieNode* nexts[NUMBER];
  TrieNode() {
    pass = 0;
    end = 0;
    for (int i = 0; i < NUMBER; i++) {
      nexts[i] = nullptr;
    }
  }
  ~TrieNode() {
    for (int i = 0; i < NUMBER; i++) {
      if (nexts[i])
        delete nexts[i];
    }
  }
};

// 所调用的树结构
class TrieTree {
  TrieNode* root = nullptr;

 public:
  TrieTree() {
    root = new TrieNode();
  }
  // 插入
  void insert(string word) {
    TrieNode* cur = root;
    cur->pass++;
    for (int i = 0; i < word.size(); i++) {  // 遍历字符串
      int num = word[i] - 'a';               // 取出这个字符在数组中的对应位置
      if (cur->nexts[num] == nullptr) {      // 查看之前有没有通向这个字符的路
        cur->nexts[num] = new TrieNode();    // 没有就新建
      }
      cur = cur->nexts[num];  // 通过这条路走向下一个节点
      cur->pass++;            // 路过这个节点的记录 +1
    }
    cur->end++;  // 在字符串走完后的最后一个节点 +1
  }
  // 查找字符串数量
  int find(string word) {
    TrieNode* cur = root;
    for (int i = 0; i < word.size(); i++) {
      int num = word[i] - 'a';
      if (cur->nexts[num] == nullptr) // 类如加入过abc，但要查abcd加入过几次，返回0
        return 0;

      cur = cur->nexts[num];
    }
    return cur->end;
  }
  // 查找前缀数量
  int findContain(string word) {
    TrieNode* cur = root;
    for (int i = 0; i < word.size(); i++) {
      int num = word[i] - 'a';
      if (cur->nexts[num] == nullptr)
        return 0;

      cur = cur->nexts[num];
    }
    return cur->pass;
  }
  // 删除
  bool erase(string word) {
    if (find(word) == 0)
      return false;
    TrieNode* cur = root;
    for (int i = 0; i < word.size(); i++) {
      int num = word[i] - 'a';
      // 问题：从上往下找节点，释放掉第一个 <=1 的节点，后面的节点没有被释放掉
      // 解决：使用哈希表或栈记录下哪些点需要被释放，整体操作完后进行释放
      if (cur->nexts[num]->pass <= 1) { 
        delete cur->nexts[num]; // 当前位置是统计过这个字符串的最后一个，释放掉
        cur->nexts[num] = nullptr;
        return true;
      }
      cur = cur->nexts[num];
      cur->pass--;
    }
    cur->end--;
    return true;
  }
};
