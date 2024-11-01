#pragma once

#include <vector>
#include <string>

//namespace TRIE_STATIC
//{

constexpr int MAX_NODE_INDEX = 5;

class Trie
{
public:
    Trie()
    {

    }

    virtual ~Trie()
    {

    }
    void Insert(const std::string& word)
    {
        int index = 0;
        pass[index]++;

        for (char c : word)
        {
            int i = c - 'a';
            if (tree[index][i] == 0)
            {
                tree[index][i] = ++nodeIndex;
            }
            index = tree[index][i];
            pass[index]++;
        }
        end[index]++;
    }

    int Search(const std::string& word)
    {
        int index = 0;
        for (char c : word)
        {
            int i = c - 'a';
            if (tree[index][i] == 0)
            {
                return 0;
            }
            index = tree[index][i];
        }
        return end[index];
    }

    int PrefixCount(const std::string& prefix)
    {
        int index = 0;
        for (char c : prefix)
        {
            int i = c - 'a';
            if (tree[index][i] == 0)
            {
                return 0;
            }
            index = tree[index][i];
        }
        return pass[index];
    }

    void Delete(const std::string& word)
    {
        if (PrefixCount(word) == 0)
        {
            return;
        }

        int index = 0;
        pass[index]--;

        for (char c : word)
        {
            int i = c - 'a';
            pass[tree[index][i]]--;

            if (pass[tree[index][i]] == 0)
            {
                tree[index][i] = 0;
                return;
            }
            index = tree[index][i];
        }
        end[index]--;
    }

private:
    std::vector<std::vector<int>> tree = std::vector<std::vector<int>>(MAX_NODE_INDEX, std::vector<int>(26, 0));
    std::vector<int> pass = std::vector<int>(MAX_NODE_INDEX, 0);
    std::vector<int> end = std::vector<int>(MAX_NODE_INDEX, 0);

    int nodeIndex = 0;
};

//}