#ifndef NUMBER_RANGE_HPP
#define NUMBER_RANGE_HPP

#include <stdexcept>
#include <iostream>

namespace ssd {

/**
 * @class NumberRange
 * @brief Defines the possible range boundaries for generating numbers.
 *
 * This class manages and validates the range boundaries from which numbers can be generated,
 * ensuring that they are logically set so that a valid game number can be chosen.
 */
    class NumberRange {
    public:
        /**
         * @brief Default constructor for NumberRange.
         */
        NumberRange() = default;

        /**
         * @brief Constructs a NumberRange with specified borders.
         *
         * Validates and sets the range borders for generating numbers. Throws std::invalid_argument if the borders are not logically set.
         *
         * @param ll Lower boundary of the left border.
         * @param hl Higher boundary of the left border.
         * @param lr Lower boundary of the right border.
         * @param hr Higher boundary of the right border.
         */
        NumberRange(int ll, int hl, int lr, int hr);

        /**
         * @brief Gets the lower boundary of the left border.
         * @return int The lower boundary of the left border.
         */
        int getLowLeftBorder() const;

        /**
         * @brief Gets the higher boundary of the left border.
         * @return int The higher boundary of the left border.
         */
        int getHighLeftBorder() const;

        /**
         * @brief Gets the lower boundary of the right border.
         * @return int The lower boundary of the right border.
         */
        int getLowRightBorder() const;

        /**
         * @brief Gets the higher boundary of the right border.
         * @return int The higher boundary of the right border.
         */
        int getHighRightBorder() const;

        /**
         * @brief Sets new borders for the range.
         *
         * Revalidates and sets new boundaries for the range. Throws std::invalid_argument if the new borders are not logically set.
         *
         * @param ll New lower boundary of the left border.
         * @param hl New higher boundary of the left border.
         * @param lr New lower boundary of the right border.
         * @param hr New higher boundary of the right border.
         */
        void setBorders(int ll, int hl, int lr, int hr);

    private:
        int lowLeftBorder; ///< The lower boundary of the left border.
        int highLeftBorder; ///< The higher boundary of the left border.
        int lowRightBorder; ///< The lower boundary of the right border.
        int highRightBorder; ///< The higher boundary of the right border.

        /**
         * @brief Checks the validity of the current borders.
         *
         * Validates the logical consistency of the range borders. Throws std::invalid_argument if borders are inconsistent.
         */
        void checkBorders() const;
    };

}

#endif // NUMBER_RANGE_HPP
