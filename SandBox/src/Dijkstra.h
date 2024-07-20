#pragma once

/*
使用最小堆来处理搜索节点，从最小堆弹出时，其最小距离就确定了
distance[i] 源点到 i 点的最短距离
visit[i] 是否从最小堆弹出过

访问 u 的一条边 v:
distance[u] + w < distance[v] 把 (distance[u] + w, v) 加入最小堆
*/

#include <vector>
#include <queue>
#include <iostream>

/*
@n    : 顶点个数
@edges: 边的关系 vector<int> edge [a, b, w]
*/
void DijkstraSolver(int n, std::vector<std::vector<int>>& edges)
{
    std::vector<std::vector<std::pair<int, int>>> relation(n);
    for (int i = 0; i < edges.size(); i++)
    {
        int a = edges[i][0], b = edges[i][1], w = edges[i][2];
        relation[a].push_back({ b, w });

        // 无向图代码逻辑 
        //relation[b].push_back({ a, w });
    }

    std::vector<int> distance(n, INT_MAX);
    distance[0] = 0;

    std::vector<bool> visit(n, false);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> que;
    que.push({ 0, 0 });

    while (!que.empty())
    {
        std::pair<int, int> cur = que.top();
        que.pop();

        if (visit[cur.second])
        {
            continue;
        }
        visit[cur.second] = true;

        for (std::pair<int, int>& edge : relation[cur.second])
        {
            int dis = cur.first + edge.second;
            if (!visit[edge.first] && dis < distance[edge.first])
            {
                distance[edge.first] = dis;
                que.push({ dis, edge.first });
            }
        }

        std::cout << "--------------------------" << std::endl;
        for (int i = 0; i < n; i++)
        {
            std::cout << distance[i] << " ";
        }
        std::cout << std::endl;
    }
}