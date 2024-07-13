#pragma once
/*
题目描述:
A、B两个人玩抢 7 游戏，游戏规则如下:

A先报一个起始数字 X（10 ≤ 起始数字 ≤ 10000），B报下一个数字 Y （X - Y < 3），A再报一个数字 Z（Y - Z < 3）;
以此类推，直到其中一个抢到7，抢到7即为胜者;

在B赢得比赛的情况下，一共有多少种组合？

思路:
动态规划:
dp[0][i] A报数i的组合数量 
dp[1][i] B报数i的组合数量

转移方程:
dp[0][i] = dp[1][i + 1] + dp[1][i + 2]
dp[1][i] = dp[0][i + 1] + dp[0][i + 2];

初始状态:
dp[0][M] = 1;
dp[1][M - 1] = 1;

*/

#include <iostream>
#include <vector>

namespace SEVEN_COMBINE
{

void backTracing(int& result, int num, int index)
{
    if (num <= 7)
    {
        if (num == 7 && index == 1)
        {
            result++;
        }
        return;
    }

    index = (index + 1) % 2;
    backTracing(result, num - 1, index);
    backTracing(result, num - 2, index);
}

int SevenCombine()
{
    int M;
    std::cin >> M;

    std::vector<std::vector<int>> dp(2, std::vector<int>(M + 1, 0));
    dp[0][M] = 1;
    dp[1][M - 1] = 1;

    for (int i = M - 2; i >= 7; i--)
    {
        dp[0][i] = dp[1][i + 1] + dp[1][i + 2];
        dp[1][i] = dp[0][i + 1] + dp[0][i + 2];
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = M; j >= 7; j--)
        {
            std::cout << dp[i][j] << " ";
        }
        std::cout << std::endl;
    }

    int result = 0;
    backTracing(result, M, 0);

    std::cout << "------------ : " << result << std::endl;
    std::cout << "++++++++++++ : " << dp[1][7] << std::endl;

    return dp[1][7];
}

}