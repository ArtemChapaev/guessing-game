#include "UserInterface.hpp"

namespace ssd {

    const std::vector<const std::string> UserInterface::questionMarks = {"<", ">", "="};
    const std::vector<const std::string> UserInterface::questionDescriptions = {LESS_QUESTION, BIGGER_QUESTION,
                                                                                EQUAL_QUESTION};
    const std::vector<const std::string> UserInterface::correctAnswers = {LESS_TEMPLATE, BIGGER_TEMPLATE,
                                                                          EQUAL_TEMPLATE};
    const std::vector<const std::string> UserInterface::wrongAnswers = {NON_LESS_TEMPLATE, NON_BIGGER_TEMPLATE,
                                                                        NON_EQUAL_TEMPLATE};

    void UserInterface::prepareDisplay() {
        std::cout << "\033[3J\033[H\033[2J" << std::flush;
        setCursor(0, 0);

        std::cout << "Choose one from possible questions below and also number Y:" << std::endl;
        for (int i = 0; i < questionDescriptions.size(); ++i) {
            std::cout << questionMarks[i] << " means \"" << questionDescriptions[i] << "\"" << std::endl;
        }

        std::cout << "Input format: <questionMark> <questionArgument>" << std::endl;
    }

    void UserInterface::displayMessage(Questions q, bool answer, int conditionValue, int leftAttempts) {
        if (answer) {
            std::cout << correctAnswers[q];
        } else {
            std::cout << wrongAnswers[q];
        }

        std::cout << conditionValue << ". ";
        displayLeftAttempts(leftAttempts);

        std::cout << std::endl;
    }

    void UserInterface::displayMessage(int leftBorder, int rightBorder, int leftAttempts) {
        std::cout << INIT_NUMBER_TEMPLATE << leftBorder << " and " << rightBorder << ". ";
        displayLeftAttempts(leftAttempts);
        std::cout << std::endl;
    }

    void UserInterface::displayWin() {
        std::cout << WIN_STRING << std::endl;
    }

    void UserInterface::displayLoss() {
        std::cout << LOSS_STRING << std::endl;
    }

    void UserInterface::displayServerError() {
        std::cout << SERVER_ERROR_STRING << std::endl;
    }


    void UserInterface::displayLeftAttempts(int leftAttempts) {
        std::cout << LEFT_ATTEMPTS_STRING << leftAttempts;
    }

    std::pair<Questions, int> UserInterface::getUserInput() {
        char questionChar;
        int questionArgument = 0;

        int userInputResult = -1;
        while (userInputResult == -1) {
            if (std::cin >> questionChar >> questionArgument) {
                // if input is char and int, we'll check is questionChar in questionMark?
                userInputResult = processUserInput(questionChar);
                if (userInputResult == -1) {
                    std::cout << "Your input isn't correct. Available question marks: <, >, ="
                              << std::endl;
                }
            } else {
                // if user's input is bad, we clear input buffer
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Your input isn't correct. Input format: <questionMark> <questionArgument>" << std::endl;
            }
        }

        return std::make_pair(Questions(userInputResult - 1), questionArgument);
    }

    int UserInterface::processUserInput(char ch) {
        if (ch == '<') {
            return 1;
        } else if (ch == '>') {
            return 2;
        } else if (ch == '=') {
            return 3;
        } else {
            return -1;
        }
    }

    void UserInterface::setCursor(unsigned x, unsigned y) {
        std::cout << "\033[" << x << ";" << y << "H" << std::flush;
    }

} // namespace ssd
