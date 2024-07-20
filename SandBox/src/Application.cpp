#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <numeric>

#include "GraphStruct.h"

using namespace std;

int main()
{
    vector<vector<int>> edges = {
        { 0, 2, 6 },
        { 3, 2, 4 },
        { 1, 3, 2 },
        { 0, 1, 7 },
        { 1, 2, 5 },
        { 2, 0, 1 }
    };

    BuildGraph(4, edges);

    cin.get();
}