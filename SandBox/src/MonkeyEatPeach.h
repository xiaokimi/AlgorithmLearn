#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

/*
��Ŀ������
����հ�����ң���һ��������԰����������͵�ԡ���֪���԰��N��������ÿ�����϶������ӣ���������HСʱ�������
����տ��Ծ���������ҵ��ٶ�K����/Сʱ����ÿ��Сʱѡһ���������������ϳԵ�K����������ϵ���������K������ȫ���Ե���
������һСʱʣ���ʱ���ﲻ�ٳ��ҡ�
�����ϲ�������ԣ�����������������ǰ�������ӡ�
�뷵������տ�����HСʱ�ڳԵ��������ӵ���С�ٶ�K��KΪ��������������κ��ٶȶ��Բ����������ӣ��򷵻�0��

����������
��һ������ΪN�����֣�N��ʾ��������������N�����ֱ�ʾÿ����������ҵ�������
�ڶ�������Ϊһ�����֣���ʾ�����뿪��ʱ��H��
��������ͨ���ո�ָN��HΪ��������ÿ�����϶�����ң���0<N<10000��0<H<10000��

���������
�Ե�������ҵ���С�ٶ�K���޽�������쳣ʱ���0��

*/

namespace MONKEY_EAT_PEACH
{

void minEatSpeed()
{
    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);

    std::vector<int> nums;
    int num;
    int total = 0, right = 0;
    while (ss >> num)
    {
        nums.push_back(num);
        total += num;
        right = std::max(right, num);
    }

    int H;
    std::cin >> H;

    int n = nums.size();
    if (n > H)
    {
        std::cout << 0 << std::endl;
        return;
    }

    int left = (total - 1) / H + 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += (nums[i] - 1) / mid + 1;
        }

        if (sum <= H)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    std::cout << left << std::endl;
}

}