#pragma once

#include <vector>
#include <algorithm>

/*
  ʹ��ǰ׺�ʹ������ٲ�ѯ�����
  preSum[i] ����ԭ���� [0, i - 1] �ĺ�
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

    // ��ѯ���� [left, right] ��ֵ
    int left = 0, right = 3;
    int result = preSum[right + 1] - preSum[left];
}

/*
  ����Ϊ n ���������� nums �У�ѡ������һ���±� i �������� k ���±�(�����±�i)����С�����
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