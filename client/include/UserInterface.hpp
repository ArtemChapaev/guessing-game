#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <vector>
#include <iostream>

#include "Questions.hpp"

namespace ssd {

#define INIT_NUMBER_TEMPLATE "Number X was generated between "

#define WIN_STRING "You win! Congratulations!"
#define LOSS_STRING "You loss.."
#define LEFT_ATTEMPTS_STRING "Left attempts "


    class UserInterface {
    public:
        void prepareDisplay() const;

        void displayMessage(Questions, bool, int, int) const;

        void displayMessage(int, int, int) const;

        void displayLeftAttempts(int) const;

        void displayWin() const;

        void displayLoss() const;

        std::pair<Questions, int> getUserInput() const;

    private:
        const std::vector<const std::string> questionMarks = {"<", ">", "="};
        const std::vector<const std::string> questionDescriptions = {LESS_QUESTION, BIGGER_QUESTION, EQUAL_QUESTION};
        const std::vector<const std::string> correctAnswers = {LESS_TEMPLATE, BIGGER_TEMPLATE, EQUAL_TEMPLATE};
        const std::vector<const std::string> wrongAnswers = {NON_LESS_TEMPLATE, NON_BIGGER_TEMPLATE,
                                                             NON_EQUAL_TEMPLATE};

        int processUserInput(char) const;

        static void setCursor(unsigned, unsigned) ;
    };

} // ssd namespace


#endif // USER_INTERFACE_HPP
