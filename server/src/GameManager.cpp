#include "GameManager.hpp"

namespace ssd {

    GameManager::GameManager(const NumberRange &range, int attempts) : number(range), leftAttempts(attempts) {
        unsigned long valuesCount = number.rightBorder - number.leftBorder;

        if (valuesCount > 25) {
            leftAttempts = static_cast<int>(leftAttempts * (log(valuesCount) / log(5) - 1));
        }
    }

    std::pair<int, int> GameManager::getNumberBorders() const{
        return std::make_pair(number.leftBorder, number.rightBorder);
    }

    int GameManager::getLeftAttempts() const{
        return leftAttempts;
    }

    bool GameManager::checkQuestion(Questions question, int questionValue) {
        --leftAttempts;

        switch (question) {
            case Questions::less: {
                return number.number < questionValue;
            }
            case Questions::bigger: {
                return number.number > questionValue;
            }
            case Questions::equal: {
                return number.number == questionValue;
            }
            default: {
                // unreachable
            }
        }
    }

} // ssd namespace
