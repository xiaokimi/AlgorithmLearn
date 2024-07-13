#pragma once

/*
����һ���±�� 0 ��ʼ������ points ������ʾ��άƽ����һЩ����������꣬���� points[i] = [xi, yi] ��
����֮��ľ��붨��Ϊ���ǵ������پ��롣
����ǡ���Ƴ�һ���㣬�����Ƴ�����������֮�����������ܵ���Сֵ��

ƽ�������� A(x1, y1) �� B(x2, y2)
�����پ���: d(A, B) = |x1 - x2| + |y1 - y2|
�б�ѩ�����: d(A, B) = max(|x1 - x2|, |y1 - y2|)

ת��:
|x1 - x2| + |y1 - y2| = max(|x1' - x2'|, |y1' - y2'|)
���� (x', y') = (x + y, y - x)����ת45��õ�
����������������پ���ת��Ϊ��Ӧ���б�ѩ�����
d(A, B) = max(max(x') - min(x'), max(y') - min(y'))

*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int minimumDistance(std::vector<std::vector<int>>& points)
{
    std::multiset<int> sx, sy;
    for (int i = 0; i < points.size(); i++)
    {
        sx.insert(points[i][0] + points[i][1]);
        sy.insert(points[i][1] - points[i][0]);
    }

    int result = INT_MAX;
    for (int i = 0; i < points.size(); i++)
    {
        sx.erase(sx.find(points[i][0] + points[i][1]));
        sy.erase(sy.find(points[i][1] - points[i][0]));
        result = std::min(result, std::max(*sx.rbegin() - *sx.begin(), *sy.rbegin() - *sy.begin()));
        sx.insert(points[i][0] + points[i][1]);
        sy.insert(points[i][1] - points[i][0]);
    }
    return result;
}