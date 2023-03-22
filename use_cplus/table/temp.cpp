#include <iostream>
using namespace std;

typedef int DataType;
#define Node Node
#define ERROR NULL

// 构建一个节点类
class Node {
   public:
    int value;   // 数据域
    Node* next;  // 指针域
};

// 构建一个单链表类
class LinkList {
   public:
    LinkList();   // 构建一个单链表;
    ~LinkList();  // 销毁一个单链表;
    // void TravalLinkList();                         // 遍历线性表
    // int GetLength();                               // 获取线性表长度
    // bool IsEmpty();                                // 判断单链表是否为空
    // Node* Find(DataType data);                 // 查找节点
    void InsertElemAtEnd(DataType data);  // 在尾部插入指定的元素
    // void InsertElemAtIndex(DataType data, int n);  // 在指定位置插入指定元素
    void InsertElemAtHead(DataType data);  // 在头部插入指定元素
                                           // void DeleteElemAtEnd();                        // 在尾部删除元素
                                           // void DeleteAll();                              // 删除所有数据
                                           // void DeleteElemAtPoint(DataType data);         // 删除指定的数据
                                           // void DeleteElemAtHead();                       // 在头部删除节点
   private:
    Node* head;  // 头结点
};

// 初始化单链表
LinkList::LinkList() {
    head = new Node;
    head->value = 0;    // 将头结点的数据域定义为0
    head->next = NULL;  // 头结点的下一个定义为NULL
}

// 销毁单链表
LinkList::~LinkList() {
    delete head;  // 删除头结点
}

// // 遍历单链表
// void LinkList::TravalLinkList() {
//     if (head == NULL || head->next == NULL) {
//         cout << "链表为空表" << endl;
//     }
//     Node* p = head;      // 另指针指向头结点
//     while (p->next != NULL)  // 当指针的下一个地址不为空时，循环输出p的数据域
//     {
//         p = p->next;  // p指向p的下一个地址
//         cout << p->data << " ";
//     }
// }

// // 获取单链表的长度
// int LinkList::GetLength() {
//     int count = 0;             // 定义count计数
//     Node* p = head->next;  // 定义p指向头结点
//     while (p != NULL)          // 当指针的下一个地址不为空时，count+1
//     {
//         count++;
//         p = p->next;  // p指向p的下一个地址
//     }
//     return count;  // 返回count的数据
// }

// // 判断单链表是否为空
// bool LinkList::IsEmpty() {
//     if (head->next == NULL) {
//         return true;
//     }
//     return false;
// }

// // 查找节点
// Node* LinkList::Find(DataType data) {
//     Node* p = head;
//     if (p == NULL) {  // 当为空表时，报异常
//         cout << "此链表为空链表" << endl;
//         return ERROR;
//     } else {
//         while (p->next != NULL)  // 循环每一个节点
//         {
//             if (p->data == data) {
//                 return p;  // 返回指针域
//             }
//             p = p->next;
//         }
//         if (p->data == data) {
//             return p;
//         }
//         return NULL;  // 未查询到结果
//     }
// }

// 在尾部插入指定的元素
void LinkList::InsertElemAtEnd(int data) {
    Node* newNode = new Node;  // 定义一个Node结点指针newNode
    newNode->next = NULL;      // 定义newNode的数据域和指针域
    newNode->data = data;
    Node* p = head;      // 定义指针p指向头结点
    if (head == NULL) {  // 当头结点为空时，设置newNode为头结点
        head = newNode;
    } else {  // 循环知道最后一个节点，将newNode放置在最后
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newNode;
    }
}

// // 在指定位置插入指定元素
// void LinkList::InsertElemAtIndex(DataType data, int n) {
//     if (n < 1 || n > GetLength())  // 输入有误报异常
//         cout << "输入的值错误" << endl;
//     else {
//         Node* ptemp = new Node;  // 创建一个新的节点
//         ptemp->data = data;              // 定义数据域
//         Node* p = head;              // 创建一个指针指向头结点
//         int i = 1;
//         while (n > i)  // 遍历到指定的位置
//         {
//             p = p->next;
//             i++;
//         }
//         ptemp->next = p->next;  // 将新节点插入到指定位置
//         p->next = ptemp;
//     }
// }

// 在头部插入指定元素
void LinkList::InsertElemAtHead(DataType data) {
    Node* newNode = new Node;  // 定义一个Node结点指针newNode
    newNode->data = data;
    Node* p = head;      // 定义指针p指向头结点
    if (head == NULL) {  // 当头结点为空时，设置newNode为头结点
        head = newNode;
    }
    newNode->next = p->next;  // 将新节点插入到指定位置
    p->next = newNode;
}

// // 在尾部删除元素
// void LinkList::DeleteElemAtEnd() {
//     Node* p = head;      // 创建一个指针指向头结点
//     Node* ptemp = NULL;  // 创建一个占位节点
//     if (p->next == NULL) {   // 判断链表是否为空
//         cout << "单链表空" << endl;
//     } else {
//         while (p->next != NULL)  // 循环到尾部的前一个
//         {
//             ptemp = p;    // 将ptemp指向尾部的前一个节点
//             p = p->next;  // p指向最后一个节点
//         }
//         delete p;  // 删除尾部节点
//         p = NULL;
//         ptemp->next = NULL;
//     }
// }

// // 删除所有数据
// void LinkList::DeleteAll() {
//     Node* p = head->next;
//     Node* ptemp = new Node;
//     while (p != NULL)  // 在头结点的下一个节点逐个删除节点
//     {
//         ptemp = p;
//         p = p->next;
//         head->next = p;
//         ptemp->next = NULL;
//         delete ptemp;
//     }
//     head->next = NULL;  // 头结点的下一个节点指向NULL
// }

// // 删除指定的数据
// void LinkList::DeleteElemAtPoint(DataType data) {
//     Node* ptemp = Find(data);  // 查找到指定数据的节点位置
//     if (ptemp == head->next) {     // 判断是不是头结点的下一个节点，如果是就从头部删了它
//         DeleteElemAtHead();
//     } else {
//         Node* p = head;       // p指向头结点
//         while (p->next != ptemp)  // p循环到指定位置的前一个节点
//         {
//             p = p->next;
//         }
//         p->next = ptemp->next;  // 删除指定位置的节点
//         delete ptemp;
//         ptemp = NULL;
//     }
// }

// // 在头部删除节点
// void LinkList::DeleteElemAtHead() {
//     Node* p = head;
//     if (p == NULL || p->next == NULL) {  // 判断是否为空表，报异常
//         cout << "该链表为空表" << endl;
//     } else {
//         Node* ptemp = NULL;  // 创建一个占位节点
//         p = p->next;
//         ptemp = p->next;  // 将头结点的下下个节点指向占位节点
//         delete p;         // 删除头结点的下一个节点
//         p = NULL;
//         head->next = ptemp;  // 头结点的指针更换
//     }
// }

// 测试函数
int main() {
    LinkList l;
    

    system("pause");
    return 0;
}
