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
#include <fstream>

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

class MyCalendarTwo {
public:
    MyCalendarTwo() {

    }

    bool book(int startTime, int endTime) {
        for (const pair<int, int>& cur : overlaped) {
            if (cur.first < endTime && cur.second > startTime) {
                return false;
            }
        }

        for (const pair<int, int>& cur : booked) {
            if (cur.first < endTime && cur.second > startTime) {
                overlaped.push_back({ max(cur.first, startTime), min(cur.second, endTime) });
            }
        }
        booked.push_back({ startTime, endTime });
        return true;
    }
private:
    vector<pair<int, int>> overlaped;
    vector<pair<int, int>> booked;
};

int maxConsecutive(int bottom, int top, vector<int>& special) {
    int n = special.size();
    sort(special.begin(), special.end());

    if (special[0] != bottom) {
        special.insert(special.begin(), bottom);
        n++;
    }

    if (special[n - 1] != top) {
        special.push_back(top);
        n++;
    }

    int res = 0;
    for (int i = 1; i < n; i++) {
        res = max(res, special[i] - special[i - 1] - 1);
    }
    return res;
}

class MyVector {
public:
    void push_back(int num) {
        if (mSize < mCapacity) {
            mSize++;
            return;
        }

        reallocate(mCapacity + 1);
        mSize++;
    }
protected:
    void reallocate(int newCapacity) {
        int growth = mCapacity + mCapacity / 2;
        mCapacity = growth < newCapacity ? newCapacity : growth;
    }

public:
    int mSize = 0;
    int mCapacity = 0;
};

long long validSubstringCount(string word1, string word2) {
    unordered_map<char, int> nums;
    for (char c : word2) {
        nums[c]++;
    }

    long long res = 0;
    int n = word1.size(), cnt = nums.size();
    for (int i = 0, j = 0; i < n; i++) {
        if (nums.count(word1[i]) > 0) {
            nums[word1[i]]--;

            if (nums[word1[i]] == 0) {
                cnt--;
            }
        }

        while (cnt == 0) {
            res += n - i;
            if (nums.count(word1[j]) > 0) {
                nums[word1[j]]++;
                if (nums[word1[j]] == 1) {
                    cnt++;
                }
            }
            j++;
        }
    }
    return res;
}

int waysToSplitArray(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    int res = 0, cnt = 0;
    for (int i = 0; i < nums.size() - 1; i++) {
        cnt += nums[i];
        if (cnt > sum - cnt) {
            res++;
        }
    }
    return res;
}

int minSubarrays(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());

    int n = nums.size();
    vector<int> cnt(n, 0);
    int index = 0;
    int res = 0;
    for (int num : nums) {
        for (int i = index; ; i++) {
            if (cnt[i] + num <= target) {
                cnt[i] += num;
                res = max(res, i + 1);
                break;
            }
        }
    }
    return res;
}

int minOperations(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> que(nums.begin(), nums.end());

    int res = 0;
    while (que.size() >= 2 && que.top() < k) {
        int x = que.top();
        que.pop();
        int y = que.top();
        que.pop();

        que.push(min(x, y) * 2 + max(x, y));
        res++;
    }
    return res;
}

int calc(vector<int>& bits) {
    int n = bits.size();
    int num = 0;
    for (int i = 0; i < n; i++) {
        if (bits[i] > 0) {
            num += 1 << i;
        }
    }
    return num;
}

int minimumSubarrayLength(vector<int>& nums, int k) {
    vector<int> bits(32, 0);
    int res = INT_MAX;
    for (int left = 0, right = 0; right < nums.size(); right++) {
        for (int i = 0; i < 32; i++) {
            bits[i] += (nums[right] >> i) & 1;
        }

        while (left < right && calc(bits) >= k) {
            res = min(res, right - left + 1);
            for (int i = 0; i < 32; i++) {
                bits[i] -= (nums[left] >> i) & 1;
            }
            left++;
        }
    }
    return res;
}

void dfs(vector<vector<int>>& res, vector<int>& path, vector<int>& nums, unordered_set<int>& record) {
    int n = nums.size();
    if (path.size() == n) {
        res.push_back(path);
        return;
    }

    unordered_set<int> preSet;
    for (int i = 0; i < n; i++) {
        if (record.find(i) != record.end()) {
            continue;
        }

        if (preSet.find(nums[i]) != preSet.end()) {
            continue;
        }
        preSet.insert(nums[i]);

        path.push_back(nums[i]);
        record.insert(i);
        dfs(res, path, nums, record);
        record.erase(i);
        path.pop_back();
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    vector<int> path;
    unordered_set<int> record;
    dfs(res, path, nums, record);
    return res;
}

vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> result(n, vector<int>(n, 0));

    vector<vector<int>> dir = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    int i = 0, j = -1, index = 0;
    for (int num = 1; num <= n * n; num++) {
        int x = i + dir[index][0];
        int y = j + dir[index][1];
        if (i < 0 || i >= n || j < 0 || j >= n ) {
            index = (index + 1) % 4;
            x = i + dir[index][0];
            y = j + dir[index][1];
        }

        result[x][y] = num;
        i = x;
        j = y;
    }
    return result;
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();

    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (obstacleGrid[i][j] == 1) {
                continue;
            }

            if (i > 0) {
                dp[i][j] += dp[i - 1][j];
            }

            if (j > 0) {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }
    return dp[m - 1][n - 1];
}

int removeDuplicates(vector<int>& nums) {
    int index = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (index >= 1 && nums[i] == nums[index - 1]) {
            continue;
        }
        nums[index++] = nums[i];
    }
    return index;
}

vector<vector<int>> dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

int findMaxFish(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    function<int(int, int)> dfs = [&](int x, int y) -> int {
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0) {
            return 0;
        }

        int sum = grid[x][y];
        grid[x][y] = 0;
        for (auto dir : dirs) {
            sum += dfs(x + dir[0], y + dir[1]);
        }
        return sum;
    };

    int res = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            res = max(res, dfs(i, j));
        }
    }
    return res;
}

int countBalls(int lowLimit, int highLimit) {
    unordered_map<int, int> cnt;
    int res = 0;
    for (int i = lowLimit; i <= highLimit; i++) {
        int sum = 0, num = i;
        while (num) {
            sum += num % 10;
            num /= 10;
        }
        cnt[sum]++;
        res = max(res, cnt[sum]);
    }
    return res;
}

bool check(vector<int>& position, int x, int m) {
    int cnt = 1;
    int pre = position[0];
    for (int i = 1; i < position.size(); i++) {
        if (position[i] - pre >= x) {
            cnt++;
            pre = position[i];
        }
    }
    return cnt >= m;
}

int maxDistance(vector<int>& position, int m) {
    sort(position.begin(), position.end());

    int left = 1, right = position.back() - position[0];
    int res = 0;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (check(position, mid, m)) {
            res = mid;
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return res;
}

string largestTimeFromDigits(vector<int>& arr) {
    int minute = -1;
    do {
        if ((arr[0] < 2 || (arr[0] == 2 && arr[1] <= 3)) && arr[2] <= 5) {
            minute = max(minute, (arr[0] * 10 + arr[1]) * 60 + arr[2] * 10 + arr[3]);
        }
    } while (std::next_permutation(arr.begin(), arr.end()));

    std::ostringstream res;
    res << setw(2) << setfill('0') << minute / 60 << ":" << setw(2) << setfill('0') << minute % 60;
    return res.str();
}

int findSpecialInteger(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0, j = 0; j < n; j++) {
        if (arr[i] == arr[j]) {
            if ((j - i + 1) * 4 > n) {
                return arr[i];
            }
        } else {
            i = j;
        }
    }
    return 0;
}

class RangeFreqQuery {
    unordered_map<int, vector<int>> indexMap;
public:
    RangeFreqQuery(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            if (indexMap.count(arr[i]) == 0) {
                indexMap[arr[i]] = {};
            }
            indexMap[arr[i]].push_back(i);
        }
    }

    int query(int left, int right, int value) {
        if (indexMap.count(value) == 0) {
            return 0;
        }

        int left = std::lower_bound(indexMap[value].begin(), indexMap[value].end(), left) - indexMap[value].begin();
        int right = std::upper_bound(indexMap[value].begin(), indexMap[value].end(), right) - indexMap[value].begin();
        return right - left;
    }
};

int maxDistance(vector<vector<int>>& arrays) {
    int minNum = arrays[0][0], maxNum = arrays[0].back();
    int res = 0;
    for (int i = 1; i < arrays.size(); i++) {
        res = max(res, max(maxNum - arrays[i][0], arrays[i].back() - minNum));
        minNum = min(minNum, arrays[i][0]);
        maxNum = max(maxNum, arrays[i].back());
    }
    return res;
}

int minRectanglesToCoverPoints(vector<vector<int>>& points, int w) {
    unordered_set<int> pos;
    for (vector<int>& point : points) {
        pos.insert(point[0]);
    }

    vector<int> xPos(pos.begin(), pos.end());
    sort(xPos.begin(), xPos.end());

    int res = 0, pre = -1;
    for (int x : xPos) {
        if (pre == -1 || x - pre > w) {
            res++;
            pre = x;
        }
    }
    return res;
}

class FoodRatings {
    unordered_map<string, pair<int, string>> foodMap;
    unordered_map<string, set<pair<int, string>>> cuisineMap;
public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        for (int i = 0; i < foods.size(); i++) {
            foodMap[foods[i]] = { -ratings[i], cuisines[i] };
            cuisineMap[cuisines[i]].insert({ -ratings[i], foods[i] });
        }
    }

    void changeRating(string food, int newRating) {
        string cuisine = foodMap[food].second;
        pair<int, string> old = { foodMap[food].first, food };
        cuisineMap[cuisine].erase(old);
        cuisineMap[cuisine].insert({ -newRating, food });
    }

    string highestRated(string cuisine) {
        return cuisineMap[cuisine].begin()->second;
    }
};

int main()
{
    vector<int> nums = { 1, 2, 3, 3 };
    findSpecialInteger(nums);

    cin.get();
}