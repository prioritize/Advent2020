#include <vector>
#include <map>
#include <iostream>
#include <set>


using Pair = std::pair<int, int>;
using std::vector;
using std::cout;
using std::endl;
using std::map;

vector<vector<int>> fourNumberSum(vector<int> array, int targetSum) {
    map<int, vector<Pair>> pMap;
    vector<vector<int>> out;
    std::set<std::set<int>> t;


    for (int i = 0; i < array.size() - 1; ++i) {
        for (int j = i+1; j < array.size(); ++j) {
            if (pMap.count(array[i] + array[j])) {
                pMap[array[i]+array[j]].push_back({i, j});
            } else {
                vector<Pair> temp;
                temp.push_back({i, j});
                pMap.insert({array[i] + array[j], temp});
            }
        }
    }
    for (auto& [key, value] : pMap) {
        int target = targetSum - key;
        if (pMap.count(target)) {
            for (auto& v : value) {
                std::set<int> temp({v.first, v.second});
                vector<Pair> results = pMap[target];
                for (auto& r : results) {
                    std::set temp({v.first, v.second});
                    if (temp.count(r.first)) {
                        continue;
                    }
                    temp.insert(r.first);
                    if (temp.count(r.second)) {
                        continue;
                    }
                    temp.insert(r.second);
                    if (!t.count(temp)) {
                        t.insert(temp);
                    }
                }
            }
        }
    }

    for (auto& group : t) {
        vector<int> temp;        
        for (auto& value : group) {
            temp.push_back(array[value]);
        }
        out.push_back(temp);
    }
    return out;
}

int main() {
    vector<int> array({7, 6, 4, -1, 1, 2});
    fourNumberSum(array, 16);
}
