#pragma once

/*
给你一个下标从 0 开始的数组 points ，它表示二维平面上一些点的整数坐标，其中 points[i] = [xi, yi] 。
两点之间的距离定义为它们的曼哈顿距离。
请你恰好移除一个点，返回移除后任意两点之间的最大距离可能的最小值。

平面内两点 A(x1, y1) 和 B(x2, y2)
曼哈顿距离: d(A, B) = |x1 - x2| + |y1 - y2|
切比雪夫距离: d(A, B) = max(|x1 - x2|, |y1 - y2|)

转换:
|x1 - x2| + |y1 - y2| = max(|x1' - x2'|, |y1' - y2'|)
其中 (x', y') = (x + y, y - x)，旋转45°得到
故任意两点的曼哈顿距离转换为对应的切比雪夫距离
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