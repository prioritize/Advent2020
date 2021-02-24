#include <vector>
#include <iostream>
#include <list>
#include <map>

using std::vector;
using std::cout;
using std::endl;
using std::pair;
using std::list;
using Pair = pair<int, int>;
using std::map;
using std::string;

Pair addPair(Pair l, Pair r);
class SpiralTraverse {
 public:
    explicit SpiralTraverse(vector<vector<int>> array);
    vector<int> traverse();
    bool check(Pair l);
    bool move();
    bool next();

 private:
    vector<vector<bool>> visited;
    map<string, Pair> moves;
    vector<vector<int>> array;
    map<string, vector<string>> preferences;
    Pair location;
    Pair dims;
    string current;
    vector<int> out;

};
SpiralTraverse::SpiralTraverse(vector<vector<int>> array)
    : array(array), location(0, 0), dims(array.size(), array[0].size()) {
        vector<bool> temp(array[0].size(), false);
        for (int i = 0; i < array.size(); ++i) {
            visited.push_back(temp);
        }

        vector<string> down({"upRight", "downLeft", "right", "down"});
        vector<string> upRight({"upRight", "right", "down"});
        vector<string> downLeft({"downLeft", "down", "right"});
        vector<string> right({"downLeft", "upRight", "down", "right"});

        preferences["down"] = down;
        preferences["upRight"] = upRight;
        preferences["downLeft"] = downLeft;
        preferences["right"] = right;

        moves["down"] = {1, 0};
        moves["upRight"] = {-1, 1};
        moves["downLeft"] = {1, -1};
        moves["right"] = {0, 1};

        current = "down";
}
bool SpiralTraverse::check(Pair l) {
    if (l.first < 0 || l.first >= dims.first) {
        return false;
    }
    if (l.second < 0 || l.second >= dims.second) {
        return false;
    }
    if (visited[l.first][l.second]) {
        return false;
    }
    return true;
}
bool SpiralTraverse::move() {
    bool canMove;
    visited[location.first][location.second] = true;
    out.push_back(array[location.first][location.second]);
    location = addPair(location, moves[current]);
    canMove = next();
    if (!canMove) {
        out.push_back(array[location.first][location.second]);
    }
    return canMove;
}
bool SpiralTraverse::next() {
    for (auto& direction : preferences[current]) {
        if (check(addPair(location, moves[direction]))) {
            current = direction;
            return true;
        }
    }
    return false;
}
vector<int> SpiralTraverse::traverse() {
    if (array.size() == 1) {
        return array[0];
    }
    while (move()) {
        continue;
    }
    return out;
}
Pair addPair(Pair l, Pair r) {
    Pair out;
    out.first = l.first + r.first;
    out.second = l.second + r.second;
    return out;
}
vector<int> zigzagTraverse(vector<vector<int>> array) {
    SpiralTraverse st(array);
    vector<int> out = st.traverse();
    return out;
}
int main() {
    vector<int> one({1, 3, 4, 10});
    vector<int> two({2, 5, 9, 11});
    vector<int> three({6, 8, 12, 15});
    vector<int> four({7, 13, 14, 16});
    vector<vector<int>> array;
    array.push_back(one);
    array.push_back(two);
    array.push_back(three);
    array.push_back(four);
    vector<int> out = zigzagTraverse(array);
    for (auto& v : out) {
        cout << v << " ";
    }
    cout << endl;
}
