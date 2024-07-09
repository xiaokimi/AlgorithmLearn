#pragma once

#include <vector>
#include <algorithm>

void SortFunctionTemplate()
{
    std::vector<int> nums = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };

    {
        // 默认由小到大排序
        std::sort(nums.begin(), nums.end());

        // 等价方法
        std::sort(nums.begin(), nums.end(), std::less<int>());
    }

    {
        // 由大到小排序
        std::sort(nums.begin(), nums.end(), std::greater<int>());
    }
}