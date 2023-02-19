#include <iostream>
using namespace std;
// 堆
// 优先级队列结构就是堆

class Heap
{
private:
    // 两数交换
    void swap(int *arr, int i, int j)
    {
        int tmp = arr[i]; // 还是传统的稳定
        arr[i] = arr[j];
        arr[j] = tmp;
    }
public:
    // 某个数处在index位置，往上继续移动
    void heapInsert(int *arr, int index)
    {
        while (arr[index] > arr[(index - 1) / 2])
        {
            swap(arr, index, (index - 1) / 2);
            index = (index - 1) / 2;
        }
    }
    // 某个数在index位置，能否往下移动
    void heapify(int *arr, int index, int heapSize)
    {
        int left = index * 2 + 1; // 左孩子下标
        while (left < heapSize)   // 下方还有孩子的时候
        {
            int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left; // 两个孩子中，谁的值大把下标给largest
            largest = arr[largest] > arr[index] ? largest : index;                            // 父和孩子之间，谁的值大把下标给largest

            if (largest == index) // 如果还是父节点本身就退出
                break;
            swap(arr, largest, index);
            index = largest;
            left = index * 2 + 1;
        }
    }
};

