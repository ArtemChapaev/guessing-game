#include "NumberRange.hpp"

namespace ssd {

    NumberRange::NumberRange(int ll, int hl, int lr, int hr)
            : lowLeftBorder(ll),
              highLeftBorder(hl),
              lowRightBorder(lr),
              highRightBorder(hr) {
        checkBorders();
    }

    int NumberRange::getLowLeftBorder() const {
        return lowLeftBorder;
    }

    int NumberRange::getHighLeftBorder() const {
        return highLeftBorder;
    }

    int NumberRange::getLowRightBorder() const {
        return lowRightBorder;
    }

    int NumberRange::getHighRightBorder() const {
        return highRightBorder;
    }

    void NumberRange::setBorders(int ll, int hl, int lr, int hr) {
        lowLeftBorder = ll;
        highLeftBorder = hl;
        lowRightBorder = lr;
        highRightBorder = hr;

        checkBorders();
    }

    void NumberRange::checkBorders() const {
        if (lowLeftBorder >= highLeftBorder || lowRightBorder >= highRightBorder) {
            throw std::invalid_argument("[NumberRange::checkBorders] Low borders can be less than right ones");
        }
        if ((lowLeftBorder + highLeftBorder) / 2 > (lowRightBorder + highRightBorder) / 2) {
            throw std::invalid_argument(
                    "[NumberRange::checkBorders] Mean of the left border must be less than mean of the right one");
        }
    }
}
