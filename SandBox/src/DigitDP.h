#pragma once

/*
数位 DP 模板

*/

//namespace DIGIT_DP
//{

#include <string>

int dfs(std::string& str, int index, int mask, bool isLimit, bool isNum)
{
    if (index == str.size())
    {
        return isNum ? 1 : 0;
    }

    int result = 0;
    if (!isNum)
    {
        result += dfs(str, index + 1, mask, false, false);
    }

    int up = isLimit ? str[index] - '0' : 9;
    int low = isNum ? 0 : 1;
    for (int i = low; i <= up; i++)
    {
        if ((mask & (1 << i)) == 0)
        {
            result += dfs(str, index + 1, mask | (1 << i), isLimit && i == up, true);
        }
    }
    return result;
}

int countSpecialNumbers(int n)
{
    std::string str = std::to_string(n);
    return dfs(str, 0, 0, true, false);
}

//}