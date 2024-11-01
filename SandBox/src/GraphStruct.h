#pragma once

/*
包含 N 个点和 M 条边的图(无向图、有向图)的构建方式:

1.邻接矩阵 N * N
vector<vector<int>> matrix(N, vector<int>(N, weight))
matrix[i][j]: i 到 j 的权重

2.邻接表 N * m (每个点的动态边和权重)
vector<vector<pair<int, int>>> matrix(N, vector<pair<int, int>(to, weight)>>)

3.链式前向星
vector<int> head(N, -1): N 个点的起始边(-1表示没有对应的边)
vector<vector<int>> nextEdge(next 下一条边的索引, to 搜索的点, weight 到搜索点的权重)

head 和 next 构成了一个链表的指向关系

测试数据:
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
        // 邻接矩阵建图
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
        // 邻接表建图
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
        // 链式前向星建图
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