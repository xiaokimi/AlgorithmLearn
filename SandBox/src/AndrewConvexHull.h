#pragma once

#include <vector>
#include <algorithm>

class Point
{
public:
    Point(int x, int y) : X(x), Y(y) {}

    Point operator-(const Point& p) const
    {
        return Point(X - p.X, Y - p.Y);
    }

    friend int Cross(const Point& p, const Point& q)
    {
        return p.X * q.Y - p.Y * q.X;
    }

public:
    int X;
    int Y;
};

std::vector<Point> AndrewConvexHull(std::vector<Point>& trees)
{
    int n = trees.size();
    if (n < 4)
    {
        return trees;
    }

    std::sort(trees.begin(), trees.end(), [](const Point& p, const Point& q) {
        if (p.X == q.X)
        {
            return p.Y < q.Y;
        }
        return p.X < q.X;
    });

    // 点的下标索引
    std::vector<int> hull;
    std::vector<bool> used(n, false);

    // 先求凸包的下半部分
    hull.push_back(0);
    for (int i = 1; i < n; i++)
    {
        while (hull.size() > 1 && Cross(trees[hull[hull.size() - 2]] - trees[i], trees[hull.back()] - trees[i]) < 0)
        {
            used[hull.back()] = false;
            hull.pop_back();
        }
        used[i] = true;
        hull.push_back(i);
    }

    // 求凸包的上半部分
    int m = hull.size();
    for (int i = n - 2; i >= 0; i--)
    {
        if (used[i])
        {
            continue;
        }

        while (hull.size() > m && Cross(trees[hull[hull.size() - 2]] - trees[i], trees[hull.back()] - trees[i]) < 0)
        {
            used[hull.back()] = false;
            hull.pop_back();
        }
        used[i] = true;
        hull.push_back(i);
    }

    // 去掉重复的0下标位置
    hull.pop_back();

    std::vector<Point> res;
    for (int i : hull)
    {
        res.push_back(trees[i]);
    }
    return res;
}