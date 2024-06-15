#pragma once

#include <iostream>
#include <random>

// 真随机数
void GenRealRandom()
{
    std::random_device rd;
    std::cout << rd() << std::endl;
}

// random number engine
void GenRandomByEngine()
{
    std::random_device rd;

    // mt19937
    std::mt19937 mt(rd());
    std::cout << mt() << std::endl;
}

// random number distributions
void GenRandomByDistribution()
{
    std::random_device rd;
    std::mt19937 mt(rd());

    {
        // 平均分布
        std::uniform_int_distribution<int> dis(1, 100);
        std::cout << dis(mt) << std::endl;
    }

    {
        // 正太分布
        std::normal_distribution<float> dis(1, 100);
        std::cout << dis(mt) << std::endl;
    }
}