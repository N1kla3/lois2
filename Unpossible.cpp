// Лабораторная работа №2 по дисциплине ЛОИС
// Вариант 3: Проверить, непротиворечивая формула
// Выполнена студентом грруппы 821703 БГУИР Владимирский Николай Викторович


#include <iostream>
#include <unordered_map>
#include <stack>
#include "Unpossible.h"
#include "Validation.h"

constexpr char alphabet[] = {'Q', 'W', 'E','R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J',
                         'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};

const std::unordered_map<char, int> priority{
        {'(', 0},
        {'-', 6},
        {'&', 5},
        {'|', 4},
        {'<', 3},
        {'>', 3},
        {'~', 1}
};

[[nodiscard]]bool checkWithConstants(const std::unordered_map<char, bool>& vars, const std::string& str);

/** return true if formula always 0 */
bool isPossible(const std::string& str) noexcept
{
    if (!Validate(str))
    {
        std::cout << "Validation failed\n";
        return false;
    }

    std::unordered_map<char, bool> vars{};

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

    bool result = false;

    while (start < mask)
    {
        int i = 0;
        for (auto& [literal, value] : vars)
        {
            start & (1 << i) ? value = true : value = false;
            i++;
        }
		try
		{
            result = result ? result : checkWithConstants(vars, str);
		}
		catch (std::exception& e)
        {
			std::cout << "inorrect braces wrappers";
		    return false;
		}
        start++;
    }

    return !result;
}

bool PerformOperation(char op, bool first, bool second)
{
    switch (op) {
        case '&': return first && second;
        case '|': return first || second;
        case '~': return first == second;
        case '<': return !(!first && second);
        case '>': return !(first && !second);
        default: return false;
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
                if (literal == '1') values.push(true);
                else if (literal == '0') values.push(false);
                else values.push(vars.at(ch));
                return true;
            }
        }
        return false;
    };

    auto untilBrace = [&operation_stack, &values](){
		if (operation_stack.empty()) return false;
        auto copy_stack = operation_stack;
		bool flag = false;
		while (!copy_stack.empty())
        {
			if (copy_stack.top() != '(') flag = true;
			copy_stack.pop();
		}
		if (!flag) return false;

        while (!operation_stack.empty() && operation_stack.top() != '(')
        {
            if (operation_stack.top() == '-')
            {
                int temp = values.top() ? 0 : 1;
                values.pop();
                values.push(temp);
                operation_stack.pop();
            }
            else
            {
                int second = values.top();
                values.pop();
                int first = values.top();
                values.pop();
                values.push(PerformOperation(operation_stack.top(), first, second));
                operation_stack.pop();
            }
        }
        if (!operation_stack.empty()) operation_stack.pop();
		return true;
    };

    auto untilPrior = [&operation_stack, &values](int prior){
      while (!operation_stack.empty() && priority.at(operation_stack.top()) >= prior)
      {
          if (operation_stack.top() == '-')
          {
              int temp = values.top() ? 0 : 1;
              values.pop();
              values.push(temp);
              operation_stack.pop();
          }
          else if (operation_stack.top() == '(')
          {
              return;
          }
          else
          {
              int second = values.top();
              values.pop();
              int first = values.top();
              values.pop();
              values.push(PerformOperation(operation_stack.top(), first, second));
              operation_stack.pop();
          }
      }
    };

    // ALGORITHM ----------------------------


    for (auto literal : str)
    {
        if (literal == ' ') continue;
        if (literal == '(')
        {
            operation_stack.push(literal);
            continue;
        }

        if (literal == ')')
        {
            if (!untilBrace()) throw std::exception();
            continue;
        }

        if (!checkVar(literal))
        {

            if (!operation_stack.empty() && priority.at(literal) <= priority.at(operation_stack.top()))
            {
                untilPrior(priority.at(literal));
                operation_stack.push(literal);
            }
            else
            {
                operation_stack.push(literal);
            }
        }
    }
    //if (!untilBrace()) throw std::exception();
    return values.top();
}