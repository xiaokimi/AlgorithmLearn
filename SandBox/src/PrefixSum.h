#pragma once

#include <vector>
#include <algorithm>

/*
  使用前缀和处理后快速查询区间和
  preSum[i] 代表原区间 [0, i - 1] 的和
*/
void QueryRangeSum()
{
    std::vector<int> nums = { 1, 2, 3, 4, 5, 6 };

    int n = nums.size();
    std::vector<int> preSum(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        preSum[i + 1] = preSum[i] + nums[i];
    }

    // 查询区间 [left, right] 的值
    int left = 0, right = 3;
    int result = preSum[right + 1] - preSum[left];
}

/*
  长度为 n 的有序数组 nums 中，选择任意一个下标 i 和其他的 k 个下标(包含下标i)的最小距离和
*/
void GetMinSum(std::vector<int>& nums, int k)
{
    std::sort(nums.begin(), nums.end());

    int n = nums.size();
    std::vector<int> preSum(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        preSum[i + 1] = preSum[i] + nums[i];
    }

    int result = INT_MAX;
    for (int i = k; i <= n; i++)
    {
        int left = i - k;
        int mid = left + k / 2;
        int leftSum = nums[mid] * (mid - left) - (preSum[mid] - preSum[left]);
        int rightSum = (preSum[i] - preSum[mid]) - nums[mid] * (i - mid);
        result = std::min(result, leftSum + rightSum);
    }
}