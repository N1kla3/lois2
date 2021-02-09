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

const std::unordered_map<char, int> priority{
        {'(', 7},
        {'-', 6},
        {'&', 5},
        {'|', 4},
        {'<', 3},
        {'>', 3},
        {'~', 1}
};

bool checkWithConstants(const std::unordered_map<char, bool>& vars, const std::string& str);

bool isPossible(const std::string& str) noexcept
{
    if (!Validate(str))
    {
        std::cout << "Validation failed\n";
        return false;
    }

    std::unordered_map<char, bool> vars{{'1', true}, {'0', false}};

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


template<char ops>
bool performOperation(bool first, bool second)
{
    std::cout << "Wrong operation\n";
    return false;
}

template<>
bool performOperation<'&'>(bool first, bool second)
{
    return first && second;
}

template<>
bool performOperation<'|'>(bool first, bool second)
{
    return first || second;
}

// ->
template<>
bool performOperation<'>'>(bool first, bool second)
{
    return !(first && !second);
}

// <-
template<>
bool performOperation<'<'>(bool first, bool second)
{
    return !(!first && second);
}

template<>
bool performOperation<'~'>(bool first, bool second)
{
    return first == second;
}

bool checkWithConstants(const std::unordered_map<char, bool>& vars, const std::string& str)
{
    constexpr char literals[] = {'Q', 'W', 'E','R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J',
                                'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '1', '0'};

    std::stack<char> operation_stack{};
    std::stack<int> values{};

    auto checkVar = [&vars, &literals, &values](char literal) -> bool{
        for (auto ch : literals)
        {
            if (ch == literal)
            {
                values.push(vars.at(ch));
                return true;
            }
        }
        return false;
    };

    int brace_count = 0;

    for (auto literal : str)
    {
        if (literal == ' ') continue;
        if (literal == '(') brace_count++;

        if (literal == ')')
        {
            //TODO  close brace logic
        }

        if (!checkVar(literal))
        {
            operation_stack.push(literal);
        }
    }

    //TODO line ended

}