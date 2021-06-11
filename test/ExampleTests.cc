// Copyright: 2020 -- Jared Leach
#include <gtest/gtest.h>
#include "../include/Day14.hpp"

class Day14: public::testing::Test {
 public:
    DockingData d;
    InputParse input;
    Day14() {
        input = InputParse input(
            "/home/jared/Documents/GitHub/Advent2020/input/day14.txt");
        DockingData d(input.commands);
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST(ExampleTests, DemonstrateGTestMacros) {
    EXPECT_TRUE(true);
}

TEST(Day14, Input) {
    InputParse input("/home/jared/Documents/GitHub/Advent2020/input/day14.txt");
    EXPECT_EQ(13902, input.input.size()) << "File read correctly";
}

TEST(Day14, Commands) {
    InputParse input("/home/jared/Documents/GitHub/Advent2020/input/day14.txt");
    EXPECT_EQ(580, input.commands.size()) << "File read correctly";
}

TEST_F(Day14, Mask) {
    // InputParse input("/home/jared/Documents/GitHub/Advent2020/input/day14.txt");
    // DockingData d(input.commands);
    EXPECT_EQ(580, d.commands.size());
    // d.executeCommand();
    EXPECT_EQ(d.mask, "0X10110X1001000X10X00X01000X01X01101") 
    << "\n\t" << d.mask << "\n\t" << "0X10110X1001000X10X00X01000X01X01101";
    // EXPECT_EQ(, input.commands.size()) << "File read correctly";
}
