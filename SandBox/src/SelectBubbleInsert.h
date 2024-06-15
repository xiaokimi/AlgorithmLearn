#pragma once

#include <vector>

void SelectSort(std::vector<int>& nums)
{
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (nums[j] < nums[minIndex])
            {
                minIndex = j;
            }
        }

        std::swap(nums[i], nums[minIndex]);
    }
}

void BubbleSort(std::vector<int>& nums)
{
    int n = nums.size();
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 1; j <= i; j++)
        {
            if (nums[j] < nums[j - 1])
            {
                std::swap(nums[j], nums[j - 1]);
            }
        }
    }
}

void InsertSort(std::vector<int>& nums)
{
    int n = nums.size();
    for (int i = 1; i < n; i++)
    {
        for (int j = i - 1; j >= 0 && nums[j] > nums[j + 1]; j--)
        {
            std::swap(nums[j], nums[j + 1]);
        }
    }
}