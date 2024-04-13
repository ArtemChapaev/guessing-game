#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <vector>
#include <iostream>

#include "Questions.hpp"

namespace ssd {

#define INIT_NUMBER_TEMPLATE "Number X was generated between "

#define WIN_STRING "You win! Congratulations!"
#define LOSS_STRING "You loss.."
#define SERVER_ERROR_STRING "Server was disconnected"

#define LEFT_ATTEMPTS_STRING "Left attempts "

    class UserInterface {
    public:
        static std::pair<Questions, int> getUserInput();

        static void prepareDisplay();

        static void displayMessage(Questions, bool, int, int);

        static void displayMessage(int, int, int);

        static void displayLeftAttempts(int);

        static void displayWin();

        static void displayLoss();

        static void displayServerError();

    private:
        static const std::vector<const std::string> questionMarks;
        static const std::vector<const std::string> questionDescriptions;
        static const std::vector<const std::string> correctAnswers;
        static const std::vector<const std::string> wrongAnswers;

        static int processUserInput(char);

        static void setCursor(unsigned, unsigned);
    };

} // ssd namespace


#endif // USER_INTERFACE_HPP
