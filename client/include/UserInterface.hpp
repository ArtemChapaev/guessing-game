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

/**
 * @class UserInterface
 * @brief Provides static methods for displaying game-related information and processing user input.
 *
 * This class manages all user interactions in the console. It provides methods to display messages, game status,
 * and to handle user input.
 */
    class UserInterface {
    public:
        /**
         * @brief Get user input from the console.
         * @return std::pair<Questions, int> A pair containing the type of question and the associated value.
         */
        static std::pair<Questions, int> getUserInput();

        /**
         * @brief Prepares the display by clearing the console and setting up the initial view.
         */
        static void prepareDisplay();

        /**
         * @brief Displays a message with the question result and remaining attempts.
         * @param q The question asked by the user.
         * @param answer The answer to the question (true if the guess was correct).
         * @param conditionValue The number associated with the question.
         * @param leftAttempts The number of attempts left.
         */
        static void displayMessage(Questions q, bool answer, int conditionValue, int leftAttempts);

        /**
         * @brief Displays the initial message with the number range and the starting number of attempts.
         * @param leftBorder The lower boundary of the number range.
         * @param rightBorder The upper boundary of the number range.
         * @param leftAttempts The initial number of attempts.
         */
        static void displayMessage(int leftBorder, int rightBorder, int leftAttempts);

        /**
         * @brief Displays the number of attempts left.
         * @param leftAttempts The number of attempts left.
         */
        static void displayLeftAttempts(int leftAttempts);

        /**
         * @brief Displays a message indicating that the user has won the game.
         */
        static void displayWin();

        /**
         * @brief Displays a message indicating that the user has lost the game.
         */
        static void displayLoss();

        /**
         * @brief Displays a message indicating that the server has been disconnected.
         */
        static void displayServerError();

    private:
        static const std::vector<const std::string> questionMarks; ///< Symbols representing question types.
        static const std::vector<const std::string> questionDescriptions; ///< Descriptions of question types.
        static const std::vector<const std::string> correctAnswers; ///< Templates for correct answers.
        static const std::vector<const std::string> wrongAnswers; ///< Templates for wrong answers.

        /**
         * @brief Processes the user input to identify the type of question.
         * @param ch The character representing the question type.
         * @return int The index of the question type or -1 if invalid.
         */
        static int processUserInput(char ch);

        /**
         * @brief Sets the cursor position in the console for display purposes.
         * @param x The row position.
         * @param y The column position.
         */
        static void setCursor(unsigned x, unsigned y);
    };

} // namespace ssd

#endif // USER_INTERFACE_HPP
