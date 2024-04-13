#ifndef NUMBER_RANGE_HPP
#define NUMBER_RANGE_HPP

#include <stdexcept>
#include <iostream>

namespace ssd {

    class NumberRange {
    public:
        NumberRange() = default;

        NumberRange(int ll, int hl, int lr, int hr);

        int getLowLeftBorder() const;

        int getHighLeftBorder() const;

        int getLowRightBorder() const;

        int getHighRightBorder() const;

        void setBorders(int ll, int hl, int lr, int hr);

    private:
        int lowLeftBorder;
        int highLeftBorder;
        int lowRightBorder;
        int highRightBorder;

        void checkBorders() const;
    };

}

#endif // NUMBER_RANGE_HPP
