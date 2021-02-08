//
// Created by nicola on 07/02/2021.
//

#include <iostream>
#include <unordered_map>
#include <stack>
#include "Unpossible.h"
#include "Validation.h"

constexpr char alphabet[] = {'Q', 'W', 'E','R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J',
                         'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};

enum class OPERATIONS
{
    AND,
    OR,
    IMPLICATION_LEFT,
    IMPLICATION_RIGHT,
    EQUAL,
    MAX
};

bool checkWithConstants(const std::unordered_map<char, bool>& map, const std::string& str);

bool isPossible(const std::string& str) noexcept
{
    if (!Validate(str))
    {
        std::cout << "Validation failed\n";
        return false;
    }

    std::unordered_map<char, bool> vars;

    // find variables
    for (auto lit : str)
    {
        for (auto a : alphabet)
        {
            if (lit == a)
            {
                vars.insert(std::make_pair(lit, 0));
            }
        }
    }

    int mask = 1 << vars.size();
    int start = 0;

    while (start < mask)
    {
        int i = 0;
        for (auto& [literal, value] : vars)
        {
            start << i & 1 << i ? value = true : value = false;
            i++;
        }
        checkWithConstants(vars, str);
        start++;
    }

    return true;
}


template<OPERATIONS ops>
bool performOperation(bool first, bool second)
{
    std::cout << "Wrong operation\n";
    return false;
}

template<>
bool performOperation<OPERATIONS::AND>(bool first, bool second)
{
    return first && second;
}

template<>
bool performOperation<OPERATIONS::OR>(bool first, bool second)
{
    return first || second;
}

// ->
template<>
bool performOperation<OPERATIONS::IMPLICATION_LEFT>(bool first, bool second)
{
    return !(first && !second);
}

// <-
template<>
bool performOperation<OPERATIONS::IMPLICATION_RIGHT>(bool first, bool second)
{
    return !(!first && second);
}

template<>
bool performOperation<OPERATIONS::EQUAL>(bool first, bool second)
{
    return first == second;
}

bool checkWithConstants(const std::unordered_map<char, bool>& map, const std::string& str)
{

    std::stack<char> operation_stack{};
    std::stack<int> values{};

}