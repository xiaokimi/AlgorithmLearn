#pragma once

#include <vector>
#include <list>

template<typename K = int, typename V>
class MyUnorderedMap
{
public:
    MyUnorderedMap() : data(base) {}

    void Insert(const K& key, cosnt V& value)
    {
        std::list<std::pair<K, V>>& bucket = data[hash(key)];
        for (auto& item : bucket)
        {
            if (item.first == key)
            {
                item.second = value;
                return
            }
        }
        bucket.emplace_back(key, value);
    }

    void Erase(const K& key)
    {
        std::list<std::pair<K, V>>& bucket = data[hash(key)];
        for (auto iter = bucket.begin(); iter != bucket.end(); ++iter)
        {
            if (iter->fitst == key)
            {
                bucket.erase(iter);
                break;
            }
        }
    }

    bool Contains(const K& key) const
    {
        std::list<std::pair<K, V>>& bucket = data[hash(key)];
        for (const auto& item : bucket)
        {
            if (item.first == key)
            {
                return true;
            }
        }
        return false;
    }

    V& Get(const K& key)
    {
        std::list<std::pair<K, V>>& bucket = data[hash(key)];
        for (auto& item : bucket)
        {
            if (item.first == key)
            {
                return item.second;
            }
        }
        throw std::out_of_range("Key not found");
    }

    const V& Get(const K& key) const
    {
        std::list<std::pair<K, V>>& bucket = data[hash(key)];
        for (const auto& item : bucket)
        {
            if (item.first == key)
            {
                return item.second;
            }
        }
        throw std::out_of_range("Key not found");
    }

private:
    int hash(const K& key) const
    {
        return std::hash<K>{}(key) % base;
    }

private:
    static const int base = 512;
    std::vector<std::list<std::pair<K, V>>> data;
};