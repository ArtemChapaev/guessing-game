#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <utility>
#include <cmath>
#include "Questions.hpp"
#include "NumberRange.hpp"
#include "Number.hpp"

namespace ssd {

/**
 * @class GameManager
 * @brief Manages the game logic for the number guessing game.
 *
 * This class handles the game state including the secret number, checking guesses, and tracking the number of remaining attempts.
 */
    class GameManager {
    public:
        /**
         * @brief Constructs a new GameManager object.
         * @param range The range from which the secret number is generated.
         * @param attempts The initial number of attempts allowed for guessing.
         */
        GameManager(const NumberRange &range, int attempts);

        /**
         * @brief Gets the borders within which the number was generated.
         * @return std::pair<int, int> The pair of integers representing the lower and upper borders.
         */
        std::pair<int, int> getNumberBorders() const;

        /**
         * @brief Gets the number of remaining attempts the player has to guess the number.
         * @return int The number of remaining attempts.
         */
        int getLeftAttempts() const;

        /**
         * @brief Checks the player's question against the secret number and updates attempts.
         * @param question The type of question being asked (less, bigger, or equal).
         * @param questionValue The numerical value associated with the question.
         * @return bool True if the guess was correct, false otherwise.
         */
        bool checkQuestion(Questions question, int questionValue);

    private:
        Number number; ///< The secret number object that holds the value and range.
        int leftAttempts; ///< The number of attempts left for guessing the number.
    };

} // namespace ssd

#endif // GAME_MANAGER_HPP
