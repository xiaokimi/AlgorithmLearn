#pragma once

/*
索引下标 1...N 表示区间和
下标索引对应关系: 左侧(i * 2) 右侧(i * 2 + 1)
*/

#include <vector>
#include <iostream>

class SegmentTree
{
public:
    SegmentTree(const std::vector<int>& nums)
    {
        int n = nums.size();
        mMaxIndex = n - 1;

        mSums.resize(n * 4);
        mLazy.resize(n * 4);

        BuildTree(0, mMaxIndex, nums, 1);
    }

    void RangeAdd(int jobLeft, int jobRight, int value)
    {
        RangeAdd(jobLeft, jobRight, value, 0, mMaxIndex, 1);
    }

    int Query(int jobLeft, int jobRight)
    {
        return Query(jobLeft, jobRight, 0, mMaxIndex, 1);
    }

    void PrintTree()
    {
        std::cout << "--------------- print tree begin ---------------" << std::endl;
        for (int i = 1; i < mSums.size(); i++)
        {
            std::cout << mSums[i] << " ";
        }
        std::cout << "\n--------------- print tree end ---------------" << std::endl;
    }

protected:
    /*
    * left right 表示原数组的下标索引，index表示线段树数组对应的下标索引
    * index 从1开始 子下标为 [index * 2, index * 2 + 1]
    */
    void BuildTree(int left, int right, const std::vector<int>& nums, int index)
    {
        if (left == right)
        {
            mSums[index] = nums[left];
            return;
        }

        int mid = left + (right - left) / 2;
        BuildTree(left, mid, nums, index * 2);
        BuildTree(mid + 1, right, nums, index * 2 + 1);
        Up(index);
    }

    void RangeAdd(int jobLeft, int jobRight, int value, int left, int right, int index)
    {
        if (jobLeft <= left && jobRight >= right)
        {
            LazyAdd(index, value, right - left + 1);
            return;
        }

        int mid = left + (right - left) / 2;
        Down(index, mid - left + 1, right - mid);

        if (mid >= jobLeft)
        {
            RangeAdd(jobLeft, jobRight, value, left, mid, index * 2);
        }

        if (mid < jobRight)
        {
            RangeAdd(jobLeft, jobRight, value, mid + 1, right, index * 2 + 1);
        }

        Up(index);
    }

    int Query(int jobLeft, int jobRight, int left, int right, int index)
    {
        if (jobLeft <= left && jobRight >= right)
        {
            return mSums[index];
        }

        int mid = left + (right - left) / 2;
        Down(index, mid - left + 1, right - mid);

        int res = 0;
        if (mid >= jobLeft)
        {
            res += Query(jobLeft, jobRight, left, mid, index * 2);
        }

        if (mid < jobRight)
        {
            res += Query(jobLeft, jobRight, mid + 1, right, index * 2 + 1);
        }
        return res;
    }

    void Up(int index)
    {
        mSums[index] = mSums[index * 2] + mSums[index * 2 + 1];
    }

    void Down(int index, int leftCount, int rightCount)
    {
        if (mLazy[index] != 0)
        {
            LazyAdd(index * 2, mLazy[index], leftCount);
            LazyAdd(index * 2 + 1, mLazy[index], rightCount);

            mLazy[index] = 0;
        }
    }

    void LazyAdd(int index, int value, int count)
    {
        mSums[index] += value * count;
        mLazy[index] += value;
    }

private:
    int mMaxIndex;
    std::vector<int> mSums;
    std::vector<int> mLazy;
};