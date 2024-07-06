#pragma once

#include <vector>
#include <algorithm>

int FindNumberIndex(std::vector<int>& nums, int target)
{
    int left = 0, right = nums.size();
    int mid;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (nums[mid] == target)
        {
            return mid;
        }
        else if (nums[mid] > target)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    return -1;
}

// >= target ������λ��
int FindMostLeftIndex(std::vector<int>& nums, int target)
{
    int left = 0, right = nums.size();
    int index = -1, mid;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (nums[mid] >= target)
        {
            index = mid;
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    return index;
}

// <= target ������λ��
int FindMostRightIndex(std::vector<int>& nums, int target)
{
    int left = 0, right = nums.size();
    int index = -1, mid;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (nums[mid] <= target)
        {
            index = mid;
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    return index;
}

// nums[i] != nums[i + 1]
int FindPeakElement(std::vector<int>& nums)
{
    int n = nums.size();
    if (n == 1)
    {
        return 0;
    }

    if (nums[0] > nums[1])
    {
        return 0;
    }
    else if (nums[n - 1] > nums[n - 2])
    {
        return n - 1;
    }

    int left = 1, right = n - 2, index = -1, mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (nums[mid - 1] > nums[mid])
        {
            right = mid - 1;
        }
        else if (nums[mid + 1] > nums[mid])
        {
            left = mid + 1;
        }
        else
        {
            index = mid;
            break;
        }
    }

    return index;
}

// ʹ�ÿ⺯�����ж�������
void BinarySearchFunction()
{
    std::vector<int> nums = { 1, 3, 5, 7, 8, 8, 9, 11 };

    {
        // index = 4 (���� >= 8 �ĵ�һ��Ԫ���±�)
        int index = std::lower_bound(nums.begin(), nums.end(), 8) - nums.begin();
    }

    {
        // index = 6 (���� > 8 �ĵ�һ��Ԫ���±�)
        int index = std::upper_bound(nums.begin(), nums.end(), 8) - nums.begin();
    }
}