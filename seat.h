// Copyright: Jared Leach -- 2020
#ifndef SEAT_H_
#define SEAT_H_

#include <vector>
#include <string>
#include <utility>

class Seat {
 public:
    int row, col, neighborCount;
    char val;
    std::vector<std::pair<int, int>> neighbors;
    Seat(int r, int c, char v);

    void genNeighbors(std::vector<std::vector<Seat>>& seats);
    void neighborSum(std::vector<std::vector<Seat>>& seats);
    void sightNeighbors(std::vector<std::vector<Seat>>& seats);
    int look(int r_dir, int c_dir, std::vector<std::vector<Seat>>& seats);
    void modify();
};

#endif  // SEAT_H_
