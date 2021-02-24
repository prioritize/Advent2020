#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

int minRewards(vector<int> scores) {
    vector<int> rewards(scores.size(), 1);
    for (int i = 1; i < scores.size(); ++i) {
        if (scores[i] > scores[i-1]) {


            rewards[i]+=rewards[i-1];
        }
    }
    for (auto& v : rewards) {
        cout << v << " ";
    }
    cout << endl;
    for (int i = scores.size() - 2; i >= 0; --i) {
        if (scores[i] > scores[i+1]) {
            // if (rewards[i+1] == 1) {
            if (rewards[i] > rewards[i+1] + 1) {
                if (rewards[i] >= 2) {
                    continue;
                }
            }
            rewards[i] = rewards[i + 1] + 1;
            // rewards[i]+=rewards[i+1];
        }
    }
    for (auto& v : rewards) {
        cout << v << " ";
    }
    cout << endl;
    int sum = 0;
    for (auto& v : rewards) {
        sum+=v;
    }
    return sum;
}

int main() {
    vector<int> scores({0, 4, 2, 1, 3});
    minRewards(scores);
}