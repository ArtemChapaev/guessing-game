#ifndef QUESTIONS_HPP
#define QUESTIONS_HPP

namespace ssd {

#define LESS_QUESTION "Is X less than Y?"
#define BIGGER_QUESTION "Is X greater than Y?"
#define EQUAL_QUESTION "Is X equal to Y?"

#define LESS_TEMPLATE "X is less than "
#define BIGGER_TEMPLATE "X is greater than "
#define EQUAL_TEMPLATE "X is equal to "

#define NON_LESS_TEMPLATE "X is NOT less than "
#define NON_BIGGER_TEMPLATE "X is NOT greater than "
#define NON_EQUAL_TEMPLATE "X is NOT equal to "

    enum Questions {
        less, bigger, equal
    };

}

#endif // QUESTIONS_HPP
