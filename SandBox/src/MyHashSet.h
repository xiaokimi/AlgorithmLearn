#pragma once

#include <vector>
#include <list>

class MyHashSet
{
public:
    MyHashSet() : data(base) {}

    void add(int value)
    {
        int key = hash(value);
        auto iter = std::find(data[key].begin(), data[key].end(), value);
        if (iter == data[key].end())
        {
            data[key].push_back(value);
        }
    }

    void remove(int value)
    {
        int key = hash(value);
        auto iter = std::find(data[key].begin(), data[key].end(), value);
        if (iter != data[key].end())
        {
            data[key].erase(iter);
        }
    }

    bool contain(int value)
    {
        int key = hash(value);
        auto iter = std::find(data[key].begin(), data[key].end(), value);
        return iter != data[key].end();
    }

private:
    int hash(int value)
    {
        return value % base;
    }

private:
    static const int base = 769;
    std::vector<std::list<int>> data;
};