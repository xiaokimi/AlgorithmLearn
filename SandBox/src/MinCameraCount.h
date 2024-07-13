#pragma once

/*
��Ŀ����:
ĳ������ͣ������ÿ����λ�Ϸ����ж�Ӧ����������ҽ����ڵ�ǰ��λ������ǰ�������ĸ���������һ����λ
��Χ���г�ʱ�����������Ҫ�򿪣�����ĳһʱ��ͣ������ͣ���ֲ�����ͳ��������Ҫ�򿪶��ٸ��������

��������:
��һ������ m,n ��ʾ���������� 1 < m,n <= 20;
���� m �У�ÿ�� n �� 0 ���� 1��0 ��ʾ��λ��1 ��ʾ��ͣ��

�������:
���ٵ�����

ʾ������:
3 3
0 0 0
0 1 0
0 0 0

ʾ�����:
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