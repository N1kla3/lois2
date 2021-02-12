//
// Created by Nicola on 05.02.2021.
//
#include "gtest/gtest.h"
#include "../Validation.h"

TEST(ValidationTests, first)
{
    EXPECT_FALSE(Validate("asdf"));
}

TEST(ValidationTests, second)
{
    EXPECT_TRUE(Validate("A > B"));
}

TEST(ValidationTests, third)
{
    EXPECT_TRUE(Validate("((A ~ B) & C)"));
}

TEST(ValidationTests, fourth)
{
    EXPECT_TRUE(Validate("A | B | D | G"));
}

TEST(ValidationTests, five)
{
    EXPECT_FALSE(Validate("(AA & B | (C ~ B)"));
}

TEST(ValidationTests, six)
{
    EXPECT_TRUE(Validate("(G <D) ~(H> -O)"));
}

TEST(ValidationTests, empty)
{
    EXPECT_FALSE(Validate(""));
}