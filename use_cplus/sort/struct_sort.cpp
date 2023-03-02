#include <algorithm>
#include <iostream>
using namespace std;
struct node {
    int a;
    int b;
} nodes[5] = {{1, 20}, {5, 4}, {5, 6}, {7, 8}, {5, 6}};
bool cmp(const node left, const node right)  // 排序规则：按a 从大到小，若a相等，则按b从大到小
{
    if (left.a == right.a) {
        return left.b > right.b;
    } else {
        return left.a > right.a;
    }
}
int main() {
    sort(nodes, nodes + 5, cmp);
    for (int i = 0; i < 5; ++i) {
        cout << "第" << i + 1 << "个:" << nodes[i].a << "," << nodes[i].b << endl;
    }
    system("pause");
    return 0;
}
// 重载比较运算符