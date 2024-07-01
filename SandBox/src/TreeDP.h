#pragma once

/*
题目描述
小美拿到了一棵树，每个节点有一个权值。初始每个节点都是白色。 

小美有若干次操作，每次操作可以选择两个相邻的节点，如果它们都是白色且权值的乘积是完全平方数，小美就可以把这两个节点同时染红。

小美想知道，自己最多可以染红多少个节点？

输入描述
第一行输入一个正整数 n（1 <= n <= 10^5），代表节点的数量。第二行输入 n 个正整数 ai（1 <= ai <= 10^9），代表每个节点的权值。接下来的 n - 1 行，每行输入两个正整数 u，v（1 <= u, v <= n），代表节点 u 和节点 v 有一条边连接。
输出描述
输出一个整数，表示最多可以染红的节点数量。

输入示例
3
3 3 12
1 2
2 3

输出示例
2

解题思路 树形 DP 问题
dp[i][0] 表示以 i 为子树，不选择 i 这个节点进行染色，i 这棵子树可以染色的结点最大数量
dp[i][1] 表示以 i 为子树，对 i 这个节点进行染色，i 这棵子树可以染色的结点最大数量

*/

#include <vector>
#include <algorithm>

class Solution_TreeDP
{
public:
    int MaxRedNodeCount(std::vector<int>& weight, std::vector<std::vector<int>>& nodes)
    {
        int n = weight.size();
        std::vector<std::vector<int>> edges(n, std::vector<int>());

        for (int i = 0; i < n - 1; i++)
        {
            edges[nodes[i][0]].emplace_back(nodes[i][1]);
            edges[nodes[i][1]].emplace_back(nodes[i][0]);
        }

        std::vector<std::vector<int>> dp(n, std::vector<int>(2, 0));
        bfs(edges, weight, dp, 0, -1);
        return std::max(dp[0][0], dp[0][1]);
    }

    void bfs(std::vector<std::vector<int>>& edges, std::vector<int>& weight, std::vector<std::vector<int>>& dp, int cur, int parent)
    {
        for (int child : edges[cur]) {
            if (child == parent) {
                continue;
            }

            bfs(edges, weight, dp, child, cur);
            dp[cur][0] += std::max(dp[child][0], dp[child][1]);
        }

        for (int child : edges[cur]) {
            if (child == parent) {
                continue;
            }

            if (!isValid(weight[child], weight[cur])) {
                continue;
            }

            dp[cur][1] = std::max(dp[cur][1], dp[cur][0] - std::max(dp[child][0], dp[child][1]) + dp[child][0] + 2);
        }
    }

    bool isValid(int x, int y)
    {
        long long mul = 1LL * x * y;
        long long num = sqrt(mul);
        return num * num == mul;
    }
};