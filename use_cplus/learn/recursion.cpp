#include <iostream>
using namespace std;
#include <vector>

class Recursion
{
public:
    int getMax(vector<int> &arr)
    {
        return process(arr, 0, arr.size() - 1);
    }
    // arr[L...R]范围上求最大值
    int process(vector<int> &arr, int L, int R)
    {
        if (L == R)
        {
            return arr[L];
        }
        int mid = L + ((R - L) >> 1);
        int leftMax = process(arr, L, mid);
        int rightMax = process(arr, mid + 1, R);
        return leftMax > rightMax ? leftMax : rightMax;
    }
};


int main()
{
    int arrTest[8] = {2, 3, 4, 5, 1, 9, 8, 3};
    vector<int> arr(arrTest, arrTest + 8);

    Recursion recursion;
    cout << recursion.getMax(arr) << endl;

    getchar();
    return 0;
}



