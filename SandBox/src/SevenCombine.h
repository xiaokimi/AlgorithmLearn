#pragma once
/*
��Ŀ����:
A��B���������� 7 ��Ϸ����Ϸ��������:

A�ȱ�һ����ʼ���� X��10 �� ��ʼ���� �� 10000����B����һ������ Y ��X - Y < 3����A�ٱ�һ������ Z��Y - Z < 3��;
�Դ����ƣ�ֱ������һ������7������7��Ϊʤ��;

��BӮ�ñ���������£�һ���ж�������ϣ�

˼·:
��̬�滮:
dp[0][i] A����i��������� 
dp[1][i] B����i���������

ת�Ʒ���:
dp[0][i] = dp[1][i + 1] + dp[1][i + 2]
dp[1][i] = dp[0][i + 1] + dp[0][i + 2];

��ʼ״̬:
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