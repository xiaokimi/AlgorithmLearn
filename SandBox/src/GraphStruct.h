#pragma once

/*
���� N ����� M ���ߵ�ͼ(����ͼ������ͼ)�Ĺ�����ʽ:

1.�ڽӾ��� N * N
vector<vector<int>> matrix(N, vector<int>(N, weight))
matrix[i][j]: i �� j ��Ȩ��

2.�ڽӱ� N * m (ÿ����Ķ�̬�ߺ�Ȩ��)
vector<vector<pair<int, int>>> matrix(N, vector<pair<int, int>(to, weight)>>)

3.��ʽǰ����
vector<int> head(N, -1): N �������ʼ��(-1��ʾû�ж�Ӧ�ı�)
vector<vector<int>> nextEdge(next ��һ���ߵ�����, to �����ĵ�, weight ���������Ȩ��)

head �� next ������һ�������ָ���ϵ

��������:
vector<vector<int>> edges = { 
        { 0, 2, 6 }, 
        { 3, 2, 4 }, 
        { 1, 3, 2 }, 
        { 0, 1, 7 }, 
        { 1, 2, 5 }, 
        { 2, 0, 1 } 
    };
*/

#include <vector>
#include <iostream>

void BuildGraph(int n, std::vector<std::vector<int>>& edges)
{
    int m = edges.size();

    {
        // �ڽӾ���ͼ
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n, INT_MIN));

        for (int i = 0; i < m; i++)
        {
            int a = edges[i][0], b = edges[i][1], w = edges[i][2];
            matrix[a][b] = w;
        }

        std::cout << "build graph by matrix:" << std::endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][j] != INT_MIN)
                {
                    std::cout << i << " ----> " << j << " : " << matrix[i][j] << std::endl;
                }
            }
        }
    }

    {
        // �ڽӱ�ͼ
        std::vector<std::vector<std::pair<int, int>>> graph(n);

        for (int i = 0; i < m; i++)
        {
            int a = edges[i][0], b = edges[i][1], w = edges[i][2];
            graph[a].push_back({ b, w });
        }

        std::cout << "build graph by list:" << std::endl;
        for (int i = 0; i < n; i++)
        {
            for (const std::pair<int, int>& edge : graph[i])
            {
                std::cout << i << " ----> " << edge.first << " : " << edge.second << std::endl;
            }
        }
    }

    {
        // ��ʽǰ���ǽ�ͼ
        std::vector<int> head(n, -1);
        std::vector<std::vector<int>> nextEdge(m, std::vector<int>(3, -1));

        for (int i = 0; i < m; i++)
        {
            int a = edges[i][0], b = edges[i][1], w = edges[i][2];
            nextEdge[i][1] = b;
            nextEdge[i][2] = w;

            // head -> next -> next -> next
            nextEdge[i][0] = head[a];
            head[a] = i;
        }

        std::cout << "build graph by nextEdge:" << std::endl;
        for (int i = 0; i < n; i++)
        {
            for (int a = head[i]; a >= 0; a = nextEdge[a][0])
            {
                std::cout << i << " ----> " << nextEdge[a][1] << " : " << nextEdge[a][2] << std::endl;
            }
        }
    }
    
}