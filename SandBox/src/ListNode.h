#pragma once

#include <vector>
#include <queue>

struct ListNode
{
    ListNode() : val(0), next(nullptr) {}
    ListNode(int v) : val(v), next(nullptr) {}
    ListNode(int v, ListNode* node) : val(v), next(node) {}

    int val = 0;
    ListNode* next = nullptr;
};

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
{
    ListNode *dummyNode = new ListNode();

    ListNode *cur = dummyNode;
    while (list1 && list2)
    {
        if (list1->val < list2->val)
        {
            cur->next = list1;
            list1 = list1->next;
        }
        else
        {
            cur->next = list2;
            list2 = list2->next;
        }
        cur = cur->next;
    }
    cur->next = list1 ? list1 : list2;

    ListNode *head = dummyNode->next;
    delete dummyNode;
    return head;
}

ListNode* mergeKLists(std::vector<ListNode*>& lists)
{
    auto cmp = [](ListNode *list1, ListNode *list2) {
        return list1->val > list2->val;
    };

    std::priority_queue < ListNode*, std::vector<ListNode*>, decltype(cmp)> que;
    for (int i = 0; i < lists.size(); i++)
    {
        if (lists[i])
        {
            que.push(lists[i]);
        }
    }

    ListNode *dummyHead = new ListNode();
    ListNode *cur = dummyHead;
    while (!que.empty())
    {
        ListNode *temp = que.top();
        que.pop();
        if (temp->next)
        {
            que.push(temp->next);
        }

        cur->next = temp;
        cur = cur->next;
    }

    ListNode *head = dummyHead->next;
    delete dummyHead;
    return head;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    ListNode *dummyHead = new ListNode();
    ListNode *cur = dummyHead;
    int sum = 0;
    while (l1 || l2 || sum != 0)
    {
        if (l1)
        {
            sum += l1->val;
            l1 = l1->next;
        }

        if (l2)
        {
            sum += l2->val;
            l2 = l2->next;
        }

        cur->next = new ListNode(sum % 10);
        sum /= 10;

        cur = cur->next;
    }

    ListNode *head = dummyHead->next;
    delete dummyHead;
    return head;
}

ListNode* partition(ListNode* head, int x)
{
    ListNode *left = new ListNode();
    ListNode *p = left;

    ListNode *right = new ListNode();
    ListNode *q = right;

    while (head)
    {
        if (head->val < x)
        {
            p->next = head;
            p = p->next;
        }
        else
        {
            q->next = head;
            q = q->next;
        }
        head = head->next;
    }

    p->next = right->next;
    q->next = nullptr;

    head = left->next;
    delete left;
    delete right;
    return head;
}