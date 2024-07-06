#pragma once

// ���Լ��
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

// ��С������
int LCM(int x, int y)
{
    int c = GCD(x, y);
    return x * y / c;
}

// ͬ��Ԫԭ��
void ModTemplate()
{
    {
        // �ӷ�ͬ��
        int a = 100, b = 999;
        int mod = 17;

        int c = (a + b) % mod;
        int d = (a % mod + b % mod) % mod;
    }

    {
        // ����ͬ��
        int a = 100, b = 999;
        int mod = 17;

        int c = (a - b) % mod;
        int d = (a % mod - b % mod + mod) % mod;
    }

    {
        // �˷�ͬ��
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

// [1...N] ��ͬʱ���� k % x != 0 && k % y != 0 �ĸ���
int CalTotalCount(int N, int x, int y)
{
    int a = N / x;
    int b = N / y;
    int c = N / LCM(x, y);

    return N - (a + b - c);
}