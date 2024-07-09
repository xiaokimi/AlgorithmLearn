/*
宝宝和妈妈参加亲子游戏，在一个二维矩阵(N * N)的格子地图上，宝宝和妈妈抽签决定各自的位置，地
图上每个格了有不同的糖果数量，部分格了有障碍物。
游戏规则是妈妈必须在最短的时间(每个单位时间只能走一步)到达宝宝的位置，路上的所有糖果都可
以拿走，不能走障碍物的格子，只能上下左右走。
请问妈妈在最短到达宝宝位置的时间内最多拿到多少糖果(优先考虑最短时间到达的情况下尽可能多拿糖果)。

输入描述
第一行输入为 N，N 标识二维知阵的大小
之后 N 行，每行有 N 个值，表格知阵每个位置的值

其中:
-3: 妈妈
-2: 宝宝
-1: 障碍
>=0: 糖果数(0表示没有糖果，但是可以走)

 4
 3  2  1 -3
 1 -1  1  1
 1  1 -1  2
-2  1  2  3

 4
 3  2  1 -3
-1 -1  1  1
 1  1 -1  2
-2  1 -1  3

*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

namespace CANDY_GET
{

int N;
vector<vector<int>> matrix;
vector<vector<bool>> visit;
pair<int, int> startPos, endPos;
int minRoadLen = INT_MAX;
int maxCandyCount = -1;

vector<vector<int>> dir = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

void dfs(int row, int col, int roadLen, int candyCount)
{
    if (endPos.first == row && endPos.second == col)
    {
        if (roadLen == minRoadLen)
        {
            maxCandyCount = max(maxCandyCount, candyCount);
        }
        else if (roadLen < minRoadLen)
        {
            minRoadLen = roadLen;
            maxCandyCount = candyCount;
        }
        return;
    }

    if (matrix[row][col] > 0)
    {
        candyCount += matrix[row][col];
    }

    for (int i = 0; i < 4; i++)
    {
        int x = row + dir[i][0];
        int y = col + dir[i][1];
        if (x >= 0 && x < N && y >= 0 && y < N && !visit[x][y] && matrix[x][y] != -1)
        {
            visit[x][y] = true;
            dfs(x, y, roadLen + 1, candyCount);
            visit[x][y] = false;
        }
    }
}

void maxCandyGet()
{
    cin >> N;

    matrix = vector<vector<int>>(N, vector<int>(N, 0));
    visit = vector<vector<bool>>(N, vector<bool>(N, false));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> matrix[i][j];
            if (matrix[i][j] == -3)
            {
                startPos.first = i;
                startPos.second = j;
            }
            else if (matrix[i][j] == -2)
            {
                endPos.first = i;
                endPos.second = j;
            }
        }
    }

    visit[startPos.first][startPos.second] = true;
    dfs(startPos.first, startPos.second, 0, 0);
    cout << maxCandyCount << endl;
}

}