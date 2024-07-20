#pragma once

/*
并查集结构:
1.自己挂自己，通过顶部节点位置做合并操作
2.在 Find 的过程中进行路径展开扁平化，加快后续的查找
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