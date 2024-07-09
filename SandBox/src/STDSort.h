#pragma once

#include <vector>
#include <algorithm>

void SortFunctionTemplate()
{
    std::vector<int> nums = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };

    {
        // Ĭ����С��������
        std::sort(nums.begin(), nums.end());

        // �ȼ۷���
        std::sort(nums.begin(), nums.end(), std::less<int>());
    }

    {
        // �ɴ�С����
        std::sort(nums.begin(), nums.end(), std::greater<int>());
    }
}