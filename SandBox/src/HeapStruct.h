#pragma once
/*
最大堆:每个根节点的值都大于等于子节点
插入操作:先插入队尾，然后递归向上调整
删除操作:将队尾放到队头，然后递归向下调整

以 vector 作为中间容器为例，父子节点下标关系:
父节点下标为 i 的子节点为: [i * 2 + 1] [i * 2 + 2]
字节点下标为 i 的父节点为: (i - 1) / 2

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

            // 向下调整
            n--;

            int index = 0;
            while (index < n)
            {
                // 判断左右孩子中较大的位置
                int maxIndex = index;
                for (int i = index * 2 + 1; i < n && i <= index * 2 + 2; i++)
                {
                    if (mNums[maxIndex] < mNums[i])
                    {
                        maxIndex = i;
                    }
                }

                // 没找到，说明当前节点就是最大的了
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
        // 默认是大顶堆
        std::priority_queue<int> ss;

        // 等价于
        std::priority_queue<int, std::vector<int>, std::less<int>> ss2;
    }

    {
        // 小顶堆
        std::priority_queue<int, std::vector<int>, std::greater<int>> ss;
    }
}