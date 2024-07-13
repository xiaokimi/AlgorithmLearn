#pragma once
/*
��Ŀ����:
�������壨�����й�����͹������壩�е����ӣ��߷���ÿ��ֱһ����бһ�񣬼��Ⱥ��Ż���ֱ����һ��Ȼ����б����һ���Խ��ߣ�
�ɽ����ˣ���Խ���ӽ磬�׳�"������"�֡�

���� m �� n �е����̣�����ͼ����������ֻ�����������е����ӡ���������ÿ�������еȼ�֮�֣�
�ȼ�Ϊ k ��������� 1~k �����ߵķ�ʽ�������С����Ĺ���һ���������Գ�������λ�ã���
���Ƿ��ܽ�����������ͬһλ�ã�������ڣ����������Ҫ���ܲ�����ÿƥ��Ĳ�����ӣ��������������-1��

ע������ͬ���������Ĺ���������ͬһλ�ã�����Ϊ��x,y��������һ�ο�������������Ϊ��
(x+1, y+2)��(x+1, y-2)��(x+2, y+1)��(x+2, y-1)��(x-1, y+2)��(x-1, y-2)��(x-2, y+1)��(x-2, y-1)��
�ĸ���ϣ����ǲ����Գ������̷�Χ��

��������:
��һ������m��n������ m �� n �е�����ͼ���̣�1 �� m, n �� 25��
���������� m �� n �е�����ͼ���̣������ i �У��� j �е�Ԫ��Ϊ "0" ������˸��û�����ӣ�
���Ϊ���� k��1 �� k �� 9��������˸����ڵȼ�Ϊ k �ġ���

�������:
���������Ҫ���ܲ�����ÿƥ��Ĳ�����ӣ��������������-1��

����ʾ��:
3 2
0 0
2 0
0 0

���:
0

����ʾ��:
3 5
4 7 0 4 8
4 7 4 4 0
7 0 0 0 0

���:
17

˼·:
ͨ�� bfs ������ͳ��ÿ��ֵΪ k ���������������������λ���Լ������Ĳ���
vector<vector<pair<int, int>>> record ��������λ��Ϊ board[i][j] ��λ�ÿ��Ե������ƥ��������С����

*/

#include <iostream>
#include <vector>
#include <queue>

int minJumpCount()
{
    int m, n;
    std::cin >> m >> n;

    std::vector<std::vector<int>> board(m, std::vector<int>(n, 0));
    std::vector<std::vector<int>> horses;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> board[i][j];
            if (board[i][j] > 0)
            {
                horses.push_back({ i, j });
            }
        }
    }

    std::vector<std::vector<int>> dir = { {1, 2}, {1, -2}, {2, 1}, {2, -1}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};

    int result = INT_MAX;
    std::vector<std::vector<std::pair<int, int>>> record(m, std::vector<std::pair<int, int>>(n, std::pair<int, int>(0, 0)));
    for (std::vector<int>& horse : horses)
    {
        std::vector<std::vector<bool>> visit(m, std::vector<bool>(n, false));
        visit[horse[0]][horse[1]] = true;

        std::queue<std::vector<int>> ss;
        ss.push(horse);
        int step = 0;
        std::cout << "***********************************************" << std::endl;
        while (!ss.empty())
        {
            int size = ss.size();
            for (int i = 0; i < size; i++)
            {
                std::vector<int> jumpHorse = ss.front();
                ss.pop();

                std::cout << "----- : " << jumpHorse[0] << ", " << jumpHorse[1] << std::endl;

                record[jumpHorse[0]][jumpHorse[1]].first++;
                record[jumpHorse[0]][jumpHorse[1]].second += step;

                if (record[jumpHorse[0]][jumpHorse[1]].first == horses.size())
                {
                    result = std::min(result, record[jumpHorse[0]][jumpHorse[1]].second);
                }

                for (int k = 0; k < 8; k++)
                {
                    int x = jumpHorse[0] + dir[k][0];
                    int y = jumpHorse[1] + dir[k][1];
                    if (x >= 0 && x < m && y >= 0 && y < n && !visit[x][y] && step < board[horse[0]][horse[1]])
                    {
                        visit[x][y] = true;
                        ss.push({ x, y });
                    }
                }
            }
            std::cout << std::endl;
            step++;
        }
    }

    return (result == INT_MAX) ? -1 : result;
}