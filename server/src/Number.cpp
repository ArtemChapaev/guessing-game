#include "Number.hpp"

#include <iostream>

namespace ssd {

    Number::Number(const NumberRange& range) {
        leftBorder = rand() % (range.highLeftBorder - range.lowLeftBorder) + range.lowLeftBorder;
        rightBorder = rand() % (range.highRightBorder - range.lowRightBorder) + range.lowRightBorder;
        number = rand() % (rightBorder - leftBorder) + leftBorder;

        std::cout << "[Number::Number] number is " << number << std::endl;
    }

} // ssd namespace
