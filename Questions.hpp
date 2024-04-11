#ifndef QUESTIONS_HPP
#define QUESTIONS_HPP

namespace ssd {

#define LESS_QUESTION "Is number X less than Y?"
#define BIGGER_QUESTION "Is number X greater than Y?"
#define EQUAL_QUESTION "Is number X equal to Y?"

#define LESS_TEMPLATE "Number X is less than "
#define BIGGER_TEMPLATE "Number X is greater than "
#define EQUAL_TEMPLATE "Number X is equal to "

#define NON_LESS_TEMPLATE "Number X is not less than "
#define NON_BIGGER_TEMPLATE "Number X is not greater than "
#define NON_EQUAL_TEMPLATE "Number X is not equal to "

    enum Questions {
        less, bigger, equal
    };

}

#endif // QUESTIONS_HPP
