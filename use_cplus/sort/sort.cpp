#include <iostream>
using namespace std;
#include "heap.cpp"
#include "radix.cpp"

template <class T>
int intgetArrayLen(T &array)
{
    return sizeof(array) / sizeof(array[0]);
}

class SelectionSort
{
private:
    // 两数交换
    void swap(int *arr, int i, int j)
    {
        // arr[i] = arr[i] + arr[j];    // 在某些情况下会出问题
        // arr[j] = arr[i] - arr[j];
        // arr[i] = arr[i] - arr[j];

        int tmp = arr[i]; // 还是传统的稳定
        arr[i] = arr[j];
        arr[j] = tmp;

        // arr[i] = arr[i] ^ arr[j];    // 在某些情况下会出问题
        // arr[j] = arr[i] ^ arr[j];
        // arr[i] = arr[i] ^ arr[j];
    }

public:
    // 选择排序
    void selectionSort(int *arr, int len)
    {
        if (len == 0)
            return; // 最后一个数不需要做比较
        for (int i = 0; i < len - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < len; j++) // 从i位置的下一个数开始遍历
            {
                minIndex = arr[j] < arr[minIndex] ? j : minIndex; // 记录最小数的下标
            }
            swap(arr, i, minIndex);
        }
    }
    // 冒泡排序
    void bubbleSort(int *arr, int len)
    {
        if (len == 0)
            return;
        for (int i = len - 1; i > 0; i--) // 每次循环把 0-i 位置上最大的放到i位置
        {
            for (int j = 0; j < i; j++) // 0-i 位置循环找最大的那个
            {
                if (arr[j] > arr[j + 1]) // 把大的放后面
                {
                    swap(arr, j, j + 1);
                }
            }
        }
    }
    // 插入排序
    void insertionSort(int *arr, int len)
    {
        if (len == 0)
            return;
        for (int i = 1; i < len; i++) // 0~0位置有序的，0~i位置想有序
        {
            for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--) // 每次把有序区的下一个元素加入并进行比较和交换
            {
                swap(arr, j, j + 1);
            }
        }
    }
    // void quickSort(int *arr, int len)
    // {
    // }
    // 堆排序
    // 时间复杂度：O(N*logN)  空间复杂度：O(1)
    void heapSort(int *arr, int len)
    {
        Heap heap;
        if (len == 0)
            return;
        // -------------------------------- 两种选择 --------------------------------
        // 构建大根堆更快的方法：将数组默认为一个堆，从数组最后一个数开始做heapify
        // for (int i = len-1;i>=0;i--)
        // {
        //     heap.heapify(arr, i, len);
        // }

        for (int i = 0; i < len; i++) // O(N) 构建大根堆，一个一个往里塞
        {
            heap.heapInsert(arr, i); // O(logN)
        }
        // --------------------------------------------------------------------------
        int heapSize = len;
        swap(arr, 0, --heapSize); // 将最后一个叶子节点和堆顶位置交换，并将最后一个数退出堆
        while (heapSize > 0)      // O(N)
        {
            heap.heapify(arr, 0, heapSize); // O(logN) 此时堆顶位置是较小的数，向下移动
            swap(arr, 0, --heapSize);       // O(1) 将最后一个叶子节点和堆顶位置交换，并将最后一个数退出堆
        }
    }
    // 桶排序
    // 非比较的排序都必须分析数据状况
    void radixSort(int *arr, int len)
    {
        Radix radix;
        radix.radixSort(arr, 0, len - 1, radix.maxBits(arr, len));
    }
};

int main()
{
    SelectionSort sort;
    int arr[] = {4, 6, 2, 91, 8, 3, 12, 32, 3, 109, 54, 23, 0};
    sort.radixSort(arr, intgetArrayLen(arr));
    // 打印排好序的数组
    for (int i = 0; i < intgetArrayLen(arr); i++)
    {
        cout << arr[i] << '-';
    }

    getchar();
    return 0;
}
