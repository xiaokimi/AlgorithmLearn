#pragma once

/*
处理逻辑同 Dijkstra 算法，只是在最小堆中的距离需要加上一个到终点的预估距离

预估距离的方法:
1.使用曼哈顿距离 d(A, B) = |Ax - Bx| + |Ay - By|
2.使用切比雪夫距离 d(A, B) = max(|Ax - Bx|, |Ay - By|)
*/

#include <vector>
#include <queue>
#include <iostream>

int GetManhattanDistance(int startX, int startY, int targetX, int targetY)
{
    return abs(startX - targetX) + abs(startY - targetY);
}

int GetChebyshevDistance(int startX, int startY, int targetX, int targetY)
{
    return std::max(abs(startX - targetX), abs(startY - targetY));
}

int AStarSolver(std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& path, std::vector<int>& start, std::vector<int>& target)
{
    int m = graph.size(), n = graph[0].size();
    std::vector<std::vector<int>> distance(m, std::vector<int>(n, INT_MAX));
    distance[start[0]][start[1]] = 0;

    std::vector<std::vector<bool>> visit(m, std::vector<bool>(n, false));
    std::priority_queue<std::pair<int, std::vector<int>>, std::vector<std::pair<int, std::vector<int>>>, std::greater<std::pair<int, std::vector<int>>>> que;
    que.push({ 0, { start[0], start[1] } });

    std::vector<std::vector<int>> dir = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

    while (!que.empty())
    {
        std::vector<int> cur = que.top().second;
        que.pop();
        if (visit[cur[0]][cur[1]])
        {
            continue;
        }
        visit[cur[0]][cur[1]] = true;
        path.push_back(cur);

        if (cur[0] == target[0] && cur[1] == target[1])
        {
            return distance[target[0]][target[1]];
        }

        for (int i = 0; i < 4; i++)
        {
            int x = cur[0] + dir[i][0];
            int y = cur[1] + dir[i][1];
            if (x >= 0 && x < m && y >= 0 && y < n && !visit[x][y] && graph[x][y] == 1 && distance[cur[0]][cur[1]] + 1 < distance[x][y])
            {
                distance[x][y] = distance[cur[0]][cur[1]] + 1;
                int len = distance[x][y] + GetManhattanDistance(target[0], target[1], x, y);
                que.push({ len, {x, y} });
            }
        }
    }

    return -1;
}