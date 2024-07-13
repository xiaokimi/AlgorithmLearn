#pragma once

/*
题目描述:
某长方形停车场，每个车位上方都有对应监控器，当且仅当在当前车位，或者前后左右四个方向任意一个车位
范围内有车时，监控器才需要打开，给出某一时刻停车场的停车分布，请统计最少需要打开多少给监控器。

输入描述:
第一行输入 m,n 表示长宽，且满足 1 < m,n <= 20;
后面 m 行，每行 n 个 0 或者 1，0 表示空位，1 表示已停车

输出描述:
最少的数量

示例输入:
3 3
0 0 0
0 1 0
0 0 0

示例输出:
5

*/

#include <iostream>
#include <vector>

void MinCameraCount()
{
    int m, n;
    std::cin >> m >> n;

    std::vector<std::vector<int>> graph(m, std::vector<int>(n, 0));
    std::vector<std::pair<int, int>> posMap;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> graph[i][j];
            if (graph[i][j] == 1)
            {
                posMap.push_back({ i, j });
            }
        }
    }

    std::vector<std::vector<int>> dir = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

    int count = posMap.size();
    for (int i = 0; i < posMap.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int x = posMap[i].first + dir[j][0];
            int y = posMap[i].second + dir[j][1];
            if (x >= 0 && x < m && y >= 0 && y < n && graph[x][y] == 0)
            {
                count++;
                graph[x][y] = 1;
            }
        }
    }
    std::cout << count << std::endl;
}