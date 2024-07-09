#pragma once

/*
问题描述:
LYA是一位热爱水果的小猴子。最近,她来到一个果园,发现里面种植了许多串香蕉,这些香蕉串排成一行。每串香蕉上有若干根香蕉,数量不等。
LYA打算采摘这些香蕉,但有一个规定:每次她只能从行的开头或末尾采摘一串香蕉,并且总共只能采摘 N 次。
LYA想知道,在这个限制下,她最多能采摘到多少根香蕉?

输入格式:
第一行包含一个正整数 n 表示香蕉串的数量。
第二行包含 n 个正整数 a1,a2,...,an,其中 ai 表示第 i 串香蕉上的香蕉根数。
第三行包含一个正整数 N,表示LYA能够采摘的次数。

输出格式:
输出一个正整数,表示LYA最多能采摘到的香蕉根数。

样例输入:
7
1 2 2 7 3 6 1
3
样例输出:
10

样例输入:
3
1 2 3
3
样例输出:
6

样例输入:
4
4 2 2 3
2
样例输出:
7

数据范围:
1 ≤ n ≤ 100000
1 ≤ ai ≤100
1 ≤ N ≤n

*/

#include <iostream>
#include <vector>
#include <algorithm>

namespace MAX_EAT_BANANA
{

void maxEatBanana()
{
    int n;
    std::cin >> n;

    std::vector<int> nums(n, 0);
    for (int i = 0; i < n; i++)
    {
        std::cin >> nums[i];
    }

    int N;
    std::cin >> N;

    int sum = 0;
    for (int i = 0; i < n - N; i++)
    {
        sum += nums[i];
    }

    int total = sum;
    int minNum = sum;
    for (int i = n - N; i < n; i++)
    {
        sum += nums[i];
        sum -= nums[i - (n - N)];
        minNum = std::min(minNum, sum);

        total += nums[i];
    }

    std::cout << total - minNum << std::endl;
}

}