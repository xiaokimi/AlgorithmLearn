#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace TRIE_DYNAMIC
{

struct TrieNode
{
    int pass = 0;
    int end = 0;
    std::vector<TrieNode*> children = std::vector<TrieNode*>(26);
};

class Trie
{
public:
    Trie()
    {
        root = new TrieNode();
    }

    virtual ~Trie()
    {
        if (root)
        {
            Clear(root);
            root = nullptr;
        }
    }

    void Insert(const std::string& word)
    {
        TrieNode *parent = root;
        parent->pass++;

        for (char c : word)
        {
            int index = c - 'a';
            if (parent->children[index] == nullptr)
            {
                parent->children[index] = new TrieNode();
            }

            parent = parent->children[index];
            parent->pass++;
        }
        parent->end++;
    }

    int Search(const std::string& word)
    {
        const TrieNode* parent = root;
        for (char c : word)
        {
            int index = c - 'a';
            if (!parent->children[index])
            {
                return 0;
            }

            parent = parent->children[index];
        }

        return parent->end;
    }

    int PrefixCount(const std::string& prefix)
    {
        const TrieNode* parent = root;
        for (char c : prefix)
        {
            int index = c - 'a';
            if (!parent->children[index])
            {
                return 0;
            }

            parent = parent->children[index];
        }

        return parent->pass;
    }

    void Delete(const std::string& word)
    {
        if (PrefixCount(word) == 0)
        {
            return;
        }

        TrieNode* parent = root;
        parent->pass--;

        for (char c : word)
        {
            int index = c - 'a';
            parent->children[index]->pass--;
            if (parent->children[index]->pass == 0)
            {
                Clear(parent->children[index]);
                parent->children[index] = nullptr;
                return;
            }

            parent = parent->children[index];
        }
        parent->end--;
    }

protected:
    void Clear(TrieNode* node)
    {
        if (node == nullptr)
        {
            return;
        }

        for (TrieNode* child : node->children)
        {
            Clear(child);
        }

        delete node;
    }

private:
    TrieNode* root;
};

}