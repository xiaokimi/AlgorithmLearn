#pragma once

/*
题目描述:
给定两个只包含数字的数组a,b,调整数组a里面数字的顺序，使得尽可能多的a[i] > b[i]。
数组a和b中的数字各不相同。输出所有可以达到最优结果的a数组数量。

输入描述:
输入的第一行是数组a中的数字，其中只包含数字，每两个数字之间相隔一个空格，a数组大小不超过10
输入的第一行是数组b中的数字，其中只包含数字，每两个数字之间相隔一个空格，b数组大小不超过10

输出描述
输出所有可以达到最优结果的a数组数量

示例1
输入：
11 8 20
10 13 7

输出：1

说明：
最优结果只有一个，a=[11,20,8] ，故输出 1 。
示例2
输入：
11 12 20
10 13 7

输出：2

说明：
有两个 a 数组的排列可以达到最优结果， [12,20,11] 和 [11,20,12] ，故输出 2

*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

namespace HORSE_SORT
{

// 最优的数量
int maxWinCount = 0;
int arraySortNum = 0;

vector<int> indexMap;
vector<vector<int>> result;

void dfs(vector<int>& A, vector<int>& B, vector<bool>& visit, int index, int count)
{
    int n = A.size();
    if (index == n)
    {
        if (count > maxWinCount)
        {
            maxWinCount = count;
            arraySortNum = 1;

            result.clear();
            result.push_back(indexMap);
        }
        else if (count == maxWinCount)
        {
            arraySortNum++;
            result.push_back(indexMap);
        }
        return;
    }

    // 剪枝优化(剩余可以胜利的数量 + 已经胜利是数量) < 当前已找到的最大数量
    if ((n - index ) + count < maxWinCount)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!visit[i])
        {
            // 去重逻辑，当前数字和前一个一样，且前一个数字没有被选择，说明当前这个操作已经有了
            if (i > 0 && A[i] == A[i - 1] && !visit[i - 1])
            {
                continue;
            }

            indexMap.push_back(i);

            visit[i] = true;
            dfs(A, B, visit, index + 1, A[i] > B[index] ? count + 1 : count);
            visit[i] = false;

            indexMap.pop_back();
        }
    }
}

void maxHorseSort()
{
    string str;
    getline(cin, str);
    stringstream ss(str);

    vector<int> A;
    int num;
    while (ss >> num)
    {
        A.push_back(num);
    }

    // 清理状态
    ss.clear();
    getline(cin, str);
    ss.str(str);

    vector<int> B;
    while (ss >> num)
    {
        B.push_back(num);
    }

    sort(A.begin(), A.end());
    vector<bool> visit(A.size(), false);
    dfs(A, B, visit, 0, 0);
    cout << arraySortNum << endl;

    cout << "-------------------------------" << endl;
    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < A.size(); j++)
        {
            cout << A[result[i][j]] << " ";
        }
        cout << endl;
    }
}

}