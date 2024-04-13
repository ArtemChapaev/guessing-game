#include "Number.hpp"

namespace ssd {

    Number::Number(const NumberRange &range) : number(0), leftBorder(0), rightBorder(0) {

        while (leftBorder >= rightBorder) {
            leftBorder = rand() % (range.getHighLeftBorder() - range.getLowLeftBorder()) + range.getLowLeftBorder();
            rightBorder = rand() % (range.getHighRightBorder() - range.getLowRightBorder()) + range.getLowRightBorder();
        }

        number = rand() % (rightBorder - leftBorder) + leftBorder;

        std::cout << "[Number::Number] Generated number is " << number << std::endl;
    }

} // ssd namespace
