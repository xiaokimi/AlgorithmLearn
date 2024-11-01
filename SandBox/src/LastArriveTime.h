#pragma once

/*
问题描述:
A先生拥有一支由 M 辆车组成的车队,他需要将这些车开到 N 公里外的目的地。
由于道路只有一条单行线,车辆无法超车。每辆车的出发时间相隔 1 小时,
即第一辆车在 0 时刻出发,第二辆车在 1 时刻出发,以此类推。

不同车辆的行驶速度不同。如果一辆较快的车追上了前方的较慢车辆,它只能以前车的速度继续行驶。
A先生想知道,最后一辆车到达目的地需要多长时间?

输入格式:
第一行包含两个正整数 M 和 N,分别表示车辆数量和目的地距离(单位:公里),用空格分隔。
接下来 M 行,每行包含一个正整数 S,表示该车辆的行驶速度(单位:公里/小时)。

输出格式:
输出一个实数,表示最后一辆车到达目的地所需的时间(单位:小时),保留一位小数。

样例输入:
2 11
3
2
样例输出:
5.5

数据范围:
1 ≤ M ≤ 20
1 ≤ N ≤ 400
0 ＜ S ＜ 30

*/

#include <iostream>
#include <vector>
#include <algorithm>

void LastArriveTime()
{
    int M, N;
    std::cin >> M >> N;

    std::vector<int> nums(M, 0);
    for (int i = 0; i < M; i++)
    {
        std::cin >> nums[i];
    }

    // 每辆车到达终点的时刻点是可以确定的，那么每辆车路上花费的时间 = 时刻点 - 等待的时间
    float timePoint = 0;
    for (int i = 0; i < M; i++)
    {
        timePoint = std::max(timePoint, (1.0f * N / nums[i]) + i);
    }
    std::cout << (timePoint - (M - 1)) << std::endl;
}