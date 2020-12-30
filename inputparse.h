// Copyright: Jared Leach -- 2020
#ifndef INPUTPARSE_H_
#define INPUTPARSE_H_

#include <vector>
#include <string>
class InputParse {
 public:
    std::vector<std::vector<char>> input;
    explicit InputParse(std::string fname);
};

#endif  // INPUTPARSE_H_
