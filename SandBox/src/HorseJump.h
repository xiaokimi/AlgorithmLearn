#pragma once
/*
题目描述:
马是象棋（包括中国象棋和国际象棋）中的棋子，走法是每步直一格再斜一格，即先横着或者直者走一格，然后再斜着走一个对角线，
可进可退，可越过河界，俗称"马走日"字。

给定 m 行 n 列的棋盘（网格图），棋盘上只有棋子象棋中的棋子“马”，并且每个棋子有等级之分，
等级为 k 的马可以跳 1~k 步（走的方式与象棋中“马”的规则一样，不可以超出棋盘位置），
问是否能将所有马跳到同一位置，如果存在，输出最少需要的总步数（每匹马的步数相加），不存在则输出-1。

注：允许不同的马在跳的过程中跳到同一位置，坐标为（x,y）的马跳一次可以跳到的坐标为：
(x+1, y+2)，(x+1, y-2)，(x+2, y+1)，(x+2, y-1)，(x-1, y+2)，(x-1, y-2)，(x-2, y+1)，(x-2, y-1)，
的格点上，但是不可以超出棋盘范围。

输入描述:
第一行输入m，n，代表 m 行 n 列的网格图棋盘（1 ≤ m, n ≤ 25）
接下来输入 m 行 n 列的网格图棋盘，如果第 i 行，第 j 列的元素为 "0" ，代表此格点没有棋子，
如果为数字 k（1 ≤ k ≤ 9），代表此格点存在等级为 k 的“马”

输出描述:
输出最少需要的总步数（每匹马的步数相加），不存在则输出-1。

输入示例:
3 2
0 0
2 0
0 0

输出:
0

输入示例:
3 5
4 7 0 4 8
4 7 4 4 0
7 0 0 0 0

输出:
17

思路:
通过 bfs 搜索，统计每个值为 k 的马，在棋牌上面可以跳的位置以及经过的步数
vector<vector<pair<int, int>>> record 代表棋牌位置为 board[i][j] 的位置可以到达的马匹数量和最小步数

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