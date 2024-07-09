#pragma once

/*
��Ŀ����:
��������ֻ�������ֵ�����a,b,��������a�������ֵ�˳��ʹ�þ����ܶ��a[i] > b[i]��
����a��b�е����ָ�����ͬ��������п��Դﵽ���Ž����a����������

��������:
����ĵ�һ��������a�е����֣�����ֻ�������֣�ÿ��������֮�����һ���ո�a�����С������10
����ĵ�һ��������b�е����֣�����ֻ�������֣�ÿ��������֮�����һ���ո�b�����С������10

�������
������п��Դﵽ���Ž����a��������

ʾ��1
���룺
11 8 20
10 13 7

�����1

˵����
���Ž��ֻ��һ����a=[11,20,8] ������� 1 ��
ʾ��2
���룺
11 12 20
10 13 7

�����2

˵����
������ a ��������п��Դﵽ���Ž���� [12,20,11] �� [11,20,12] ������� 2

*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

namespace HORSE_SORT
{

// ���ŵ�����
int maxWinCount = 0;
int arraySortNum = 0;

vector<int> indexMap;
vector<vector<int>> result;

void dfs(vector<int>& A, vector<int>& B, vector<bool>& visit, int index, int count)
{
    int n = A.size();
    if (index == n)
    {
        if (count > maxWinCount)
        {
            maxWinCount = count;
            arraySortNum = 1;

            result.clear();
            result.push_back(indexMap);
        }
        else if (count == maxWinCount)
        {
            arraySortNum++;
            result.push_back(indexMap);
        }
        return;
    }

    // ��֦�Ż�(ʣ�����ʤ�������� + �Ѿ�ʤ��������) < ��ǰ���ҵ����������
    if ((n - index ) + count < maxWinCount)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!visit[i])
        {
            // ȥ���߼�����ǰ���ֺ�ǰһ��һ������ǰһ������û�б�ѡ��˵����ǰ��������Ѿ�����
            if (i > 0 && A[i] == A[i - 1] && !visit[i - 1])
            {
                continue;
            }

            indexMap.push_back(i);

            visit[i] = true;
            dfs(A, B, visit, index + 1, A[i] > B[index] ? count + 1 : count);
            visit[i] = false;

            indexMap.pop_back();
        }
    }
}

void maxHorseSort()
{
    string str;
    getline(cin, str);
    stringstream ss(str);

    vector<int> A;
    int num;
    while (ss >> num)
    {
        A.push_back(num);
    }

    // ����״̬
    ss.clear();
    getline(cin, str);
    ss.str(str);

    vector<int> B;
    while (ss >> num)
    {
        B.push_back(num);
    }

    sort(A.begin(), A.end());
    vector<bool> visit(A.size(), false);
    dfs(A, B, visit, 0, 0);
    cout << arraySortNum << endl;

    cout << "-------------------------------" << endl;
    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < A.size(); j++)
        {
            cout << A[result[i][j]] << " ";
        }
        cout << endl;
    }
}

}