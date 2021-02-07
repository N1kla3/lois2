//
// Created by nicola on 07/02/2021.
//
#include "gtest/gtest.h"
#include "../Unpossible.h"

TEST(InPossibleTests, first)
{
    EXPECT_FALSE(isPossible("A ~ B"));
}

TEST(InPossibleTests, second)
{
    EXPECT_TRUE(isPossible("-A & B & A"));
}

TEST(InPossibleTests, third)
{
    EXPECT_TRUE(isPossible("0 & (B > C)"));
}

TEST(InPossibleTests, fourth)
{
    EXPECT_FALSE(isPossible("A ~ B ~ C"));
}

TEST(InPossibleTests, fivth)
{
    EXPECT_FALSE(isPossible("-A ~ B ~ A ~ -B"));
}

TEST(InPossibleTests, six)
{
    EXPECT_TRUE(isPossible("-A & (A|B) & -B"));
}

TEST(InPossibleTests, seven)
{
    EXPECT_FALSE(isPossible("(A~B)>C"));
}

TEST(InPossibleTests, eight)
{
    EXPECT_TRUE(isPossible("-(A|B)~(A|B)"));
}

TEST(InPossibleTests, nine)
{
    EXPECT_FALSE(isPossible("AA"));
}

TEST(InPossibleTests, ten)
{
    EXPECT_FALSE(isPossible("A->B"));
}
