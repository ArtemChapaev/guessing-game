#ifndef QUESTIONS_HPP
#define QUESTIONS_HPP

namespace ssd {

/**
 * @enum Questions
 * @brief Enumerates the types of questions that can be asked about the secret number.
 */
    enum Questions {
        less,    ///< Represents a question if the number is less than a certain value.
        bigger,  ///< Represents a question if the number is greater than a certain value.
        equal    ///< Represents a question if the number is equal to a certain value.
    };

#define LESS_QUESTION "Is X less than Y?"          ///< Question prompt for 'less'.
#define BIGGER_QUESTION "Is X greater than Y?"     ///< Question prompt for 'bigger'.
#define EQUAL_QUESTION "Is X equal to Y?"          ///< Question prompt for 'equal'.

#define LESS_TEMPLATE "X is less than "            ///< Response template for a correct 'less' answer.
#define BIGGER_TEMPLATE "X is greater than "       ///< Response template for a correct 'bigger' answer.
#define EQUAL_TEMPLATE "X is equal to "            ///< Response template for a correct 'equal' answer.

#define NON_LESS_TEMPLATE "X is NOT less than "    ///< Response template for an incorrect 'less' answer.
#define NON_BIGGER_TEMPLATE "X is NOT greater than " ///< Response template for an incorrect 'bigger' answer.
#define NON_EQUAL_TEMPLATE "X is NOT equal to "    ///< Response template for an incorrect 'equal' answer.

}

#endif // QUESTIONS_HPP
