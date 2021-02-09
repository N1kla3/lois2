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

bool PerformOperation(char op, bool first, bool second)
{
    switch (op) {
        case '&': return first && second;
        case '|': return first || second;
        case '~': return first == second;
        case '<': return !(!first && second);
        case '>': return !(first && !second);
        default:return false;
    }
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

    auto untilBrace = [&operation_stack, &values](){
        while (operation_stack.top() != '(')
        {
            int second = values.top(); values.pop();
            int first = values.top(); values.pop();
            values.push(PerformOperation(operation_stack.top(), first, second));
            operation_stack.pop();
        }
    };

    int brace_count = 0;
    bool perform_operation = false;

    for (auto literal : str)
    {
        if (literal == ' ') continue;
        if (literal == '(') brace_count++;

        if (literal == ')')
        {
            untilBrace();
            continue;
        }

        if (checkVar(literal))
        {
            if (perform_operation)
            {
                perform_operation = false;
                int second = values.top(); values.pop();
                int first = values.top(); values.pop();
                values.push(PerformOperation(operation_stack.top(), first, second));
                operation_stack.pop();
            }
        }
        else
        {
            if (!operation_stack.empty() && priority.at(literal) > priority.at(operation_stack.top()))
            {
                perform_operation = true;
            }
            operation_stack.push(literal);
        }
    }
    int result = values.top();
    while (!operation_stack.empty())
    {
        int second = values.top(); values.pop();
        int first = values.top(); values.pop();
        result = PerformOperation(operation_stack.top(), first, second);
        values.push(result);
        operation_stack.pop();
    }
    return result;//TODO priority perforamtion
}