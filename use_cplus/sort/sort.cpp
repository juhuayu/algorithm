#include <iostream>
using namespace std;

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
};

int main()
{
    SelectionSort sort;
    int arr[] = {4, 6, 2, 9, 8, 3};
    sort.insertionSort(arr, intgetArrayLen(arr));
    // 打印排好序的数组
    for (int i = 0; i < 6; i++)
    {
        cout << arr[i] << '-';
    }

    getchar();
    return 0;
}
