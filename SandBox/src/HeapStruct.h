#pragma once
/*
����:ÿ�����ڵ��ֵ�����ڵ����ӽڵ�
�������:�Ȳ����β��Ȼ��ݹ����ϵ���
ɾ������:����β�ŵ���ͷ��Ȼ��ݹ����µ���

�� vector ��Ϊ�м�����Ϊ�������ӽڵ��±��ϵ:
���ڵ��±�Ϊ i ���ӽڵ�Ϊ: [i * 2 + 1] [i * 2 + 2]
�ֽڵ��±�Ϊ i �ĸ��ڵ�Ϊ: (i - 1) / 2

*/

#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>

class HeapStruct
{
public:
    HeapStruct()
    {

    }

    void push(int value)
    {
        int index = mNums.size();
        mNums.push_back(value);

        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (mNums[parent] >= mNums[index])
            {
                break;
            }

            std::swap(mNums[parent], mNums[index]);
            index = parent;
        }
    }

    void pop()
    {
        int n = mNums.size();
        if (n > 0)
        {
            mNums[0] = mNums[n - 1];
            mNums.pop_back();

            // ���µ���
            n--;

            int index = 0;
            while (index < n)
            {
                // �ж����Һ����нϴ��λ��
                int maxIndex = index;
                for (int i = index * 2 + 1; i < n && i <= index * 2 + 2; i++)
                {
                    if (mNums[maxIndex] < mNums[i])
                    {
                        maxIndex = i;
                    }
                }

                // û�ҵ���˵����ǰ�ڵ����������
                if (maxIndex == index)
                {
                    break;
                }

                std::swap(mNums[maxIndex], mNums[index]);
                index = maxIndex;
            }
        }
    }

    size_t size()
    {
        return mNums.size();
    }

    bool empty()
    {
        return mNums.size() == 0;
    }

    int top()
    {
        assert(mNums.size() > 0);
        return mNums[0];
    }

private:
    std::vector<int> mNums;
};

void STD_priority_queue()
{
    {
        // Ĭ���Ǵ󶥶�
        std::priority_queue<int> ss;

        // �ȼ���
        std::priority_queue<int, std::vector<int>, std::less<int>> ss2;
    }

    {
        // С����
        std::priority_queue<int, std::vector<int>, std::greater<int>> ss;
    }
}