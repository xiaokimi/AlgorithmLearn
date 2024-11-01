#pragma once

#include <vector>
#include <iostream>
#include "RandomSample.h"

/*
  < target 的放左边 == target 的放中间 > target 的放右边
  [left, right] 为 == target 的下标索引
*/
void Partition(std::vector<int>& nums, int& left, int& right, int target)
{
    int index = left;
    while (index <= right)
    {
        if (nums[index] < target)
        {
            std::swap(nums[left++], nums[index++]);
        }
        else if (nums[index] > target)
        {
            std::swap(nums[index], nums[right--]);
        }
        else
        {
            index++;
        }
    }
}

int RandomSelect(std::vector<int>& nums, int k)
{
    int result = 0;
    int left = 0, right = nums.size() - 1;
    while (left <= right)
    {
        int index = RandomNum::GetInstance().GenRandomNum() % (right - left + 1) + left;
        int l = left, r = right;
        Partition(nums, l, r, nums[index]);
        if (k < l)
        {
            right = l - 1;
        }
        else if (k > r)
        {
            left = r + 1;
        }
        else
        {
            result = nums[k];
            break;
        }
    }
    return result;
}

int FindMaxKNum(std::vector<int>& nums, int k, int left, int right)
{
    int n = nums.size();
    int i = left, j = right;

    int num = nums[i];
    while (i < j)
    {
        while (j > i && nums[j] > num)
        {
            j--;
        }
        if (i >= j)
        {
            break;
        }
        nums[i++] = nums[j];

        while (i < j && nums[i] < num)
        {
            i++;
        }
        if (i >= j)
        {
            break;
        }
        nums[j--] = nums[i];
    }
    nums[i] = num;

    if (i + k < n)
    {
        return FindMaxKNum(nums, k, i + 1, right);
    }
    else if (i + k > n)
    {
        return FindMaxKNum(nums, k, left, i - 1);
    }
    return num;
}

// 最大的第k个数
int FindMaxKNum(std::vector<int>& nums, int k)
{
    return FindMaxKNum(nums, k, 0, nums.size() - 1);
}