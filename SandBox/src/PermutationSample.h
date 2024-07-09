#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

namespace PREMUTATION_SAMPLE
{

void dfs(std::vector<int>& nums, std::vector<bool>& visit, std::vector<int>& path, int index)
{
    int n = nums.size();
    if (index == n)
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << path[i] << " ";
        }
        std::cout << std::endl;

        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!visit[i])
        {
            if (i > 0 && nums[i] == nums[i - 1] && !visit[i - 1])
            {
                continue;
            }

            visit[i] = true;
            path.push_back(nums[i]);
            dfs(nums, visit, path, index + 1);
            path.pop_back();
            visit[i] = false;
        }
    }
}

void PermutationSample()
{
    std::vector<int> nums = { 1, 2, 3, 4, 4 };
    std::sort(nums.begin(), nums.end());

    std::vector<bool> visit(nums.size(), false);
    std::vector<int> path;
    dfs(nums, visit, path, 0);

    /*
      库函数调用
      next_permutation 下一个降序排列
      prev_permutation 下一个升序排列
    */
    do
    {
        for (int i = 0; i < nums.size(); i++)
        {
            std::cout << nums[i] << " ";
        }
        std::cout << std::endl;
    } while (std::next_permutation(nums.begin(), nums.end()));
}

}