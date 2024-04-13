#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <iostream>

#include <cstdlib>

#include "NumberRange.hpp"

namespace ssd {

    struct Number {
        explicit Number(const NumberRange&);

        int number;
        int leftBorder;
        int rightBorder;
    };

} // ssd namespace


#endif // NUMBER_HPP
