#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

void FormatNumber()
{
    // 默认输出的是6个数字的科学计数法 3.14159
    double value = 3.141592654;
    std::cout << value << std::endl;

    // 保留4位小数 3.1416
    std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
    std::cout << value << std::endl;

    // 恢复为默认输出 3.14159
    std::cout << std::setprecision(0) << std::resetiosflags(std::ios::fixed);
    std::cout << value << std::endl;
}

void SplitWord()
{
    std::stringstream ss("Hello world man");
    std::string word;

    std::vector<std::string> words;
    while (ss >> word)
    {
        words.emplace_back(word);
    }
}

void GetLineNumSplitBySpace()
{
    std::string str;
    std::getline(std::cin, str);

    std::stringstream ss(str);

    std::vector<int> nums;
    int num;
    while (ss >> num)
    {
        nums.push_back(num);
    }

    // output split nums
    for (int i = 0; i < nums.size(); i++)
    {
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;
}

void StringStreamUseSample()
{
    std::string str;
    std::getline(std::cin, str);

    std::stringstream ss(str);

    std::vector<int> nums;
    int num;
    while (ss >> num)
    {
        nums.push_back(num);
    }

    for (int i = 0; i < nums.size(); i++)
    {
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;

    // 重置状态，再次赋值
    ss.clear();
    nums.clear();

    std::getline(std::cin, str);
    ss.str(str);

    while (ss >> num)
    {
        nums.push_back(num);
    }

    for (int i = 0; i < nums.size(); i++)
    {
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;
}