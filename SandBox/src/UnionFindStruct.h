#pragma once

/*
���鼯�ṹ:
1.�Լ����Լ���ͨ�������ڵ�λ�����ϲ�����
2.�� Find �Ĺ����н���·��չ����ƽ�����ӿ�����Ĳ���
*/

#include <vector>
#include <numeric>

class UnionFindStruct
{
public:
    UnionFindStruct(int n)
    {
        mFather.resize(n);
        std::iota(mFather.begin(), mFather.end(), 0);
    }

    void Union(int x, int y)
    {
        mFather[Find(x)] = Find(y);
    }

    bool IsSame(int x, int y)
    {
        return Find(x) == Find(y);
    }

protected:
    int Find(int index)
    {
        if (mFather[index] != index)
        {
            mFather[index] = Find(mFather[index]);
        }

        return mFather[index];
    }

private:
    std::vector<int> mFather;
};