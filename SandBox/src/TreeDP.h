#pragma once

/*
��Ŀ����
С���õ���һ������ÿ���ڵ���һ��Ȩֵ����ʼÿ���ڵ㶼�ǰ�ɫ�� 

С�������ɴβ�����ÿ�β�������ѡ���������ڵĽڵ㣬������Ƕ��ǰ�ɫ��Ȩֵ�ĳ˻�����ȫƽ������С���Ϳ��԰��������ڵ�ͬʱȾ�졣

С����֪�����Լ�������Ⱦ����ٸ��ڵ㣿

��������
��һ������һ�������� n��1 <= n <= 10^5��������ڵ���������ڶ������� n �������� ai��1 <= ai <= 10^9��������ÿ���ڵ��Ȩֵ���������� n - 1 �У�ÿ���������������� u��v��1 <= u, v <= n��������ڵ� u �ͽڵ� v ��һ�������ӡ�
�������
���һ����������ʾ������Ⱦ��Ľڵ�������

����ʾ��
3
3 3 12
1 2
2 3

���ʾ��
2

����˼· ���� DP ����
dp[i][0] ��ʾ�� i Ϊ��������ѡ�� i ����ڵ����Ⱦɫ��i �����������Ⱦɫ�Ľ���������
dp[i][1] ��ʾ�� i Ϊ�������� i ����ڵ����Ⱦɫ��i �����������Ⱦɫ�Ľ���������

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