#pragma once

#include <vector>
#include <algorithm>

/*
  weight[i] 物品 i 的重量
  value[i]  物品 i 的价值
  dp[i][j]  从下标 [0-i] 的物品中任意取，放进容量为 j 的背包的最大值
  dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i])
*/

int BagSelectWithTwoDim(std::vector<int>& weight, std::vector<int>& value, int bagSize)
{
    int n = weight.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(bagSize + 1, 0));

    for (int j = weight[0]; j <= bagSize; j++)
    {
        dp[0][j] = value[0];
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= bagSize; j++)
        {
            if (j - weight[i] >= 0)
            {
                dp[i][j] = std::max(dp[i][j], dp[i - 1][j - weight[i]] + value[i]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n - 1][bagSize];
}

/*
  weight[i] 物品 i 的重量
  value[i]  物品 i 的价值
  dp[j]     容量为 j 的背包的最大值
  dp[j] = max([j], dp[j - weight[i]] + value[i])
*/

int BagSelectWithOneDim(std::vector<int>& weight, std::vector<int>& value, int bagSize)
{
    std::vector<int> dp(std::vector<int>(bagSize + 1, 0));

    for (int i = 0; i < weight.size(); i++)
    {
        for (int j = bagSize; j >= weight[i]; j--)
        {
            dp[j] = std::max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }

    return dp[bagSize];
}