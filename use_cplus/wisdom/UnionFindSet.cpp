/*
并查集
*/

#include <iostream>
#include <list>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

template <class T>
class UnionFindSet {
 private:
  class Element {
   public:
    T value;
    Element(T v)
        : value(v) {}
  };
  unordered_map<T, Element*> elementMap;        // 存放用户的数据与结构中数据的对应关系（注册的所有点）
  unordered_map<Element*, Element*> fatherMap;  // 节点对应父节点是哪个（如果没有父节点就指向自己）
  unordered_map<Element*, int> sizeMap;         // 记录所有根节点下子节点的个数
  Element* findHead(Element* element);          // 向上查找当前节点的父节点

 public:
  UnionFindSet(list<T> list);
  UnionFindSet(vector<T> list);
  ~UnionFindSet();
  bool isSameSet(T a, T b);  // 数据a和b是否在同一个集合中
  void merge(T a, T b);      // 合并数据a和数据b所在的集合
};

template <class T>
UnionFindSet<T>::UnionFindSet(list<T> list) {
  for (T value : list) {
    Element* element = new Element(value);
    elementMap.emplace(value, element);
    fatherMap.emplace(element, element);
    sizeMap.emplace(element, 1);
  }
}

template <class T>
UnionFindSet<T>::UnionFindSet(vector<T> list) {
  for (T value : list) {
    Element* element = new Element(value);
    elementMap.emplace(value, element);
    fatherMap.emplace(element, element);
    sizeMap.emplace(element, 1);
  }
}

template <class T>
UnionFindSet<T>::~UnionFindSet() {
}

template <class T>
typename UnionFindSet<T>::Element* UnionFindSet<T>::findHead(Element* element) {
  stack<Element*> path;                       // 用于优化
  while (element != fatherMap.at(element)) {  // 找父节点
    path.push(element);
    element = fatherMap.at(element);
  }
  while (!path.empty()) {  // 将所有未直接指向最上面节点点节点挨个都指向最上面的父节点（扁平化处理）
    fatherMap.at(path.top()) = element;
    path.pop();
  }
  return element;
}

template <class T>
bool UnionFindSet<T>::isSameSet(T a, T b) {
  if ((elementMap.find(a) != elementMap.end()) && (elementMap.find(b) != elementMap.end())) {  // 确认数据a和数据b都是注册过的数据
    return findHead(elementMap.at(a)) == findHead(elementMap.at(b));                           // 向上查找数据a和数据b的最顶层父节点是不是同一个节点
  }
  return false;
}

template <class T>
void UnionFindSet<T>::merge(T a, T b) {
  if ((elementMap.find(a) != elementMap.end()) && (elementMap.find(b) != elementMap.end())) {  // 确认数据a和数据b都是注册过的数据
    Element* aF = findHead(elementMap.at(a));                                                  // 拿出a数据的父节点
    Element* bF = findHead(elementMap.at(b));                                                  // 拿出b数据的父节点
    if (aF != bF) {                                                                            // 查看是不是同一个集合
      Element* big = sizeMap.at(aF) >= sizeMap.at(bF) ? aF : bF;                               // 节点下面挂着节点最多的节点
      Element* small = big == aF ? bF : aF;                                                    // 相对较少的那个
      fatherMap.at(small) = big;                                                               // 少的节点父节点指向多的那个
      sizeMap.at(big) = sizeMap.at(aF) + sizeMap.at(bF);                                       // 更新多的那个节点下挂载节点的数量
      sizeMap.erase(small);                                                                    // 删除少的那个数量记录
    }
  }
}

// int main() {
//   vector<int> testList = {1, 2, 3, 4, 5};
//   UnionFindSet<int> myset(testList);

//   myset.merge(testList[0], testList[1]);

//   cout << myset.isSameSet(testList[0], testList[1]) << endl;
//   cout << myset.isSameSet(testList[0], testList[3]) << endl;

//   system("pause");
//   return 0;
// }