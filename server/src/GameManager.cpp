#include "GameManager.hpp"

namespace ssd {

    GameManager::GameManager(const NumberRange &range, int attempts) : number(range), leftAttempts(attempts) {}

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
