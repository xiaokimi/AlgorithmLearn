#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

void FormatNumber()
{
    // Ĭ���������6�����ֵĿ�ѧ������ 3.14159
    double value = 3.141592654;
    std::cout << value << std::endl;

    // ����4λС�� 3.1416
    std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
    std::cout << value << std::endl;

    // �ָ�ΪĬ����� 3.14159
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