#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <numeric>
#include <set>
#include <array>
#include <stack>
#include <utility>
#include <functional>
#include <iomanip>
#include <bitset>

#include "RandomSample.h"
#include "SegmentTree.h"

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int rob(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(2, 0);

    for (int i = 0; i < n; i++) {
        int temp = dp[0];
        dp[0] = max(dp[0], dp[1]);
        dp[1] = temp + nums[i];
    }
    return max(dp[0], dp[1]);
}

long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
    int n = energyDrinkA.size();
    vector<vector<long long>> dp(n + 2, vector<long long>(2, 0));
    for (int i = 0; i < n; i++) {
        dp[i + 2][0] = max(dp[i + 1][0], dp[i][1]) + energyDrinkA[i];
        dp[i + 2][1] = max(dp[i + 1][1], dp[i][0]) + energyDrinkB[i];
    }
    return max(dp[n + 1][0], dp[n + 1][1]);
}

int main()
{
    int N = 20;
    int maxNum = 100;

    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        nums[i] = RandomNum::GetInstance().GenRandomNum() % maxNum;
    }

    SegmentTree s(nums);

    for (int i = 0; i < 1000; i++)
    {
        int left = RandomNum::GetInstance().GenRandomNum() % N;
        int right = RandomNum::GetInstance().GenRandomNum() % N;
        if (left > right)
        {
            swap(left, right);
        }

        int op = RandomNum::GetInstance().GenRandomNum() % 2;
        if (op == 0)
        {
            int value = RandomNum::GetInstance().GenRandomNum() % maxNum;
            for (int j = left; j <= right; j++)
            {
                nums[j] += value;
            }

            s.RangeAdd(left, right, value);
        }
        else
        {
            int sum1 = 0;
            for (int j = left; j <= right; j++)
            {
                sum1 += nums[j];
            }

            int sum2 = s.Query(left, right);
            if (sum1 != sum2)
            {
                cout << "---" << endl;
            }
        }
    }

    cin.get();
}