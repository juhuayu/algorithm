from typing import List
# 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。
# 请你找出并返回这两个正序数组的 中位数 。
# 示例：
#  输入：nums1 = [1,3], nums2 = [2]
#  输出：2.00000
#  解释：合并数组 = [1,2,3] ，中位数 2
class Solution:
    # 执行用时：40 ms, 在所有 Python3 提交中击败了93.53%的用户
    # 内存消耗：15 MB, 在所有 Python3 提交中击败了92.82%的用户
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        nums1.extend(nums2)
        nums1.sort()
        num_length = len(nums1)-1
        if(num_length%2==1):
            return (nums1[num_length//2]+nums1[num_length//2+1])/2
        else:
            return nums1[num_length//2]
            

if __name__ == '__main__':
    solution = Solution()
    arr1 = [1,2]
    arr2 = [3,4]
    print(solution.findMedianSortedArrays(arr1, arr2))
    
