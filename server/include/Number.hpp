#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <iostream>
#include <cstdlib>
#include "NumberRange.hpp"

namespace ssd {

/**
 * @struct Number
 * @brief Represents a number with its associated range.
 *
 * This struct holds the secret number and its valid range, generated within the limits defined by a NumberRange object.
 */
    struct Number {
        /**
         * @brief Constructs the Number object.
         *
         * This constructor initializes the Number with a value within the specified range. It repeatedly
         * generates random left and right borders from the provided NumberRange until a valid range is established
         * (leftBorder is less than rightBorder), and then generates the secret number within this range.
         *
         * @param range The range from which to generate the number's borders and value.
         */
        explicit Number(const NumberRange& range);

        int number;        ///< The secret number.
        int leftBorder;    ///< The lower bound of the range in which the number is generated.
        int rightBorder;   ///< The upper bound of the range in which the number is generated.
    };

} // namespace ssd

#endif // NUMBER_HPP
