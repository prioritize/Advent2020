// Copyright: 2020 -- Jared Leach
#include <gtest/gtest.h>
#include "../Example.hpp"
#include "../Day14.hpp"

TEST(ExampleTests, DemonstrateGTestMacros) {
    EXPECT_TRUE(true);
}

TEST(ExampleTests, MAC) {
    int x =  42;
    int y = 16;
    int sum = 100;
    int oldSum = sum;
    int expectedNewSum = oldSum + x * y;

    EXPECT_EQ(
        expectedNewSum,
        MAC(x, y, sum));
    EXPECT_EQ(
        expectedNewSum, sum);
}

TEST(ExampleTests, Square) {
    int x = 100;
    EXPECT_EQ(x, Square(10));
}

TEST(Day14, Input) {
    InputParse input("/home/jared/Documents/GitHub/Advent2020/day14.txt");
    EXPECT_EQ(13902, input.input.size()) << "File read correctly";
}

TEST(Day14, Commands) {
    InputParse input("/home/jared/Documents/GitHub/Advent2020/day14.txt");
    EXPECT_EQ(580, input.commands.size()) << "File read correctly";
}

TEST(Day14, Mask) {
    InputParse input("/home/jared/Documents/GitHub/Advent2020/day14.txt");
    DockingData d(input.commands);
    EXPECT_EQ(580, d.commands.size());
    d.executeCommand();
    EXPECT_EQ(d.mask, "0X10110X1001000X10X00X01000X01X01101") 
    << "\n\t" << d.mask << "\n\t" << "0X10110X1001000X10X00X01000X01X01101";
    // EXPECT_EQ(, input.commands.size()) << "File read correctly";
}
