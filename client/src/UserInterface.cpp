#include "UserInterface.hpp"

namespace ssd {
    void UserInterface::prepareDisplay() const {
        std::cout << "\033[3J\033[H\033[2J" << std::flush;
        setCursor(0, 0);

        std::cout << "Choose one from possible questions below and also number Y:" << std::endl;
        for (int i = 0; i < questionDescriptions.size(); ++i) {
            std::cout << i + 1 << " means \"" << questionDescriptions[i] << "\"" << std::endl;
        }

        std::cout << "Input format: <questionMark> <questionArgument>" << std::endl;
    }

    void UserInterface::displayMessage(Questions q, bool answer, int conditionValue, int leftAttempts) const {
        if (answer) {
            std::cout << correctAnswers[q] << " " << conditionValue << ". ";
        } else {
            std::cout << wrongAnswers[q] << " " << conditionValue << ". ";
        }
        displayLeftAttempts(leftAttempts);
        std::cout << std::endl;
    }

    void UserInterface::displayMessage(int leftBorder, int rightBorder, int leftAttempts) const {
        std::cout << INIT_NUMBER_TEMPLATE << leftBorder << " and " << rightBorder << ".";
        displayLeftAttempts(leftAttempts);
        std::cout << std::endl;
    }

    void UserInterface::displayWin() const {
        std::cout << WIN_STRING << std::endl;
    }

    void UserInterface::displayLoss() const {
        std::cout << LOSS_STRING << std::endl;
    }

    void UserInterface::displayLeftAttempts(int leftAttempts) const {
        std::cout << LEFT_ATTEMPTS_STRING << leftAttempts;
    }

    void UserInterface::setCursor(unsigned x, unsigned y) {
        std::cout << "\033[" << x << ";" << y << "H" << std::flush;
    }

    std::pair<Questions, int> UserInterface::getUserInput() const {
        int questionId = -1;
        int questionArgument = 0;

        std::cin >> questionId >> questionArgument;
        return std::make_pair(Questions(questionId - 1), questionArgument);
    }
}
