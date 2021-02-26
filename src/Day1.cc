// "Copyright: 2020 -- Jared Leach"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::vector;
using std::string;

vector<int> qsort(vector<int> report);
int find2020(vector<int> report);
int find32020(vector<int> report);
class DayOne {
 public:
    vector<int> report;
    explicit DayOne(string fname) {
        std::ifstream expenseReport;
        expenseReport.open(fname);
        std::string entry;
        if (expenseReport.is_open()) {
            while (getline(expenseReport, entry)) {
                report.push_back(stoi(entry));
            }
        }
        std::sort(report.begin(), report.end());
    }
    void printReport() {
        for (auto entry : report) {
            std::cout << entry << std::endl;
        }
    }
    int twoSum(int toFind) {
        // this->report was sorted on initialization so no need to resort
        int left = 0;
        int right = this->report.size() - 1;
        int sum = 0;
        while (left < right) {
            int sum = report[left] + report[right];
            if (sum == toFind) {
                return report[left] * report[right];
            }
            if (sum > toFind) {
                right--;
            }
            if (sum < toFind) {
                left++;
            }
        }
        // No matching values were found
        return -1;
    }
    int threeSum(int toFind) {
        int left = 0, right = report.size() - 1, mover = left + 1, sum = 0;

        while (left < right) {
            while (mover < right) {
                sum = report[left] + report[right] + report[mover];
                if (sum > toFind) {
                    right--;
                }
                if (sum < toFind) {
                    mover++;
                }
                if (sum == toFind) {
                    return report[left] * report[right] * report[mover];
                }
            }
            left++;
            mover = left + 1;
            right = report.size() - 1;
        }
        // No matching values were found
        return -1;
    }
};

int main() {
    DayOne d1("day1expensereport.txt");
    std::cout << d1.twoSum(2020) << std::endl;
    std::cout << d1.threeSum(2020) << std::endl;
    return 1;
}
