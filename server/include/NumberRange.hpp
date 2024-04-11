#ifndef NUMBER_RANGE_HPP
#define NUMBER_RANGE_HPP

namespace ssd {

    struct NumberRange {
        NumberRange() = default;

        NumberRange(int ll, int hl, int lr, int hr)
        : lowLeftBorder(ll),
          highLeftBorder(hl),
          lowRightBorder(lr),
          highRightBorder(hr)
        {}

        int lowLeftBorder{};
        int highLeftBorder{};
        int lowRightBorder{};
        int highRightBorder{};
    };

}

#endif // NUMBER_RANGE_HPP
