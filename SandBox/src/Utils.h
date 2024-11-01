#pragma once

#include <vector>
#include <algorithm>

// 最大公约数
int GCD(int x, int y)
{
    int temp;
    while (y != 0)
    {
        temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

// 最小公倍数
int LCM(int x, int y)
{
    int c = GCD(x, y);
    return x * y / c;
}

// 同余元原理
void ModTemplate()
{
    {
        // 加法同余
        int a = 100, b = 999;
        int mod = 17;

        int c = (a + b) % mod;
        int d = (a % mod + b % mod) % mod;
    }

    {
        // 减法同余
        int a = 100, b = 999;
        int mod = 17;

        int c = (a - b) % mod;
        int d = (a % mod - b % mod + mod) % mod;
    }

    {
        // 乘法同余
        int a = 100, b = 999;
        int mod = 17;

        int c = (a * b) % mod;
        int d = ((a % mod) * (b % mod)) % mod;
    }
}

bool IsPrime(int num)
{
    if (num == 1)
    {
        return false;
    }
    else if (num == 2 || num == 3 || num == 5 || num == 7)
    {
        return true;
    }
    else if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0 || num % 7 == 0)
    {
        return false;
    }

    for (int i = 3; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

// [1...N] 中同时满足 k % x != 0 && k % y != 0 的个数
int CalTotalCount(int N, int x, int y)
{
    int a = N / x;
    int b = N / y;
    int c = N / LCM(x, y);

    return N - (a + b - c);
}

// 区间合并
void mergeArray(std::vector<std::vector<int>>& ranges)
{
    std::sort(ranges.begin(), ranges.end());

    std::vector<std::vector<int>> res;
    for (int i = 0; i < ranges.size(); i++)
    {
        if (!res.empty() && res.back()[1] >= ranges[i][0])
        {
            res.back()[1] = std::max(res.back()[1], ranges[i][1]);
        }
        else
        {
            res.push_back(ranges[i]);
        }
    }
}

// 快速幂计算 (x^n) % mod
long long fastPowerMod(long long x, long long n, long long MOD)
{
    long long result = 1;
    long long base = x % MOD;
    while (n > 0)
    {
        if (n % 2 == 1)
        {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        n /= 2;
    }
    return result;
}