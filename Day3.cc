#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

class InputParse {
 public:
    vector<string> forest;

    explicit InputParse(string fname) {
        std::ifstream input;
        input.open(fname);
        string line;
        if (input.is_open()) {
            string line;
            while (getline(input, line)) {
                forest.push_back(line);
            }
        }
    }
};

class Forest {
 public:
    vector<string> forest;
    std::pair<int, int> location;
    std::pair<int, int> slope;
    vector<std::pair<int, int>> locations;
    int trees = 0;

    Forest(vector<string> inForest, std::pair<int, int> startingLoc, std::pair<int, int> inSlope) {
        forest = inForest;
        location = startingLoc;
        slope = inSlope;
        std::pair<int, int> currentLoc;
        locations.push_back(startingLoc);
        while (currentLoc.first < forest.size() - 1) {
            currentLoc = genLocation(currentLoc);
            locations.push_back(currentLoc);
        }
        countTrees();
        cout << trees << endl;
    }
    std::pair<int, int> genLocation(std::pair<int, int> movement) {
        std::pair<int, int> next;
        next.first = movement.first + slope.first;
        next.second = movement.second + slope.second;
        if (next.second >= forest[0].size()) {
            next.second = next.second - forest[0].size();
        }
        return next;
    }
    void countTrees() {
        for (auto location : locations) {
            // cout << location.first << " " << location.second << endl;
            if (forest[location.first][location.second] == '#') {
                forest[location.first][location.second] = 'X';
                trees++;
            } else {
                forest[location.first][location.second] = 'O';
            }
        }
    }
};

int main() {
    InputParse input("day3trees.txt");
    std::pair<int, int> startingLoc(0, 0);
    std::pair<int, int> slope1(1, 1);
    std::pair<int, int> slope2(1, 3);
    std::pair<int, int> slope3(1, 5);
    std::pair<int, int> slope4(1, 7);
    std::pair<int, int> slope5(2, 1);
    Forest path1(input.forest, startingLoc, slope1);
    Forest path2(input.forest, startingLoc, slope2);
    Forest path3(input.forest, startingLoc, slope3);
    Forest path4(input.forest, startingLoc, slope4);
    Forest path5(input.forest, startingLoc, slope5);

    cout << input.forest.size() << endl;
    cout << input.forest[0].size() << endl;

}