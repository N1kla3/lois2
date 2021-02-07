//
// Created by nicola on 07/02/2021.
//

#include <iostream>
#include "Unpossible.h"
#include "Validation.h"

bool isPossible(const std::string& str) noexcept
{
    if (!Validate(str))
    {
        std::cout << "Validation failed\n";
        return false;
    }
    return true;
}