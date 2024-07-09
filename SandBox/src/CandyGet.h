/*
����������μ�������Ϸ����һ����ά����(N * N)�ĸ��ӵ�ͼ�ϣ������������ǩ�������Ե�λ�ã���
ͼ��ÿ�������в�ͬ���ǹ����������ָ������ϰ��
��Ϸ�����������������̵�ʱ��(ÿ����λʱ��ֻ����һ��)���ﱦ����λ�ã�·�ϵ������ǹ�����
�����ߣ��������ϰ���ĸ��ӣ�ֻ�����������ߡ�
������������̵��ﱦ��λ�õ�ʱ��������õ������ǹ�(���ȿ������ʱ�䵽�������¾����ܶ����ǹ�)��

��������
��һ������Ϊ N��N ��ʶ��ά֪��Ĵ�С
֮�� N �У�ÿ���� N ��ֵ�����֪��ÿ��λ�õ�ֵ

����:
-3: ����
-2: ����
-1: �ϰ�
>=0: �ǹ���(0��ʾû���ǹ������ǿ�����)

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