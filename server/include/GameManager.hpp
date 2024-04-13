#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <utility>

#include <cmath>

#include "Questions.hpp"
#include "NumberRange.hpp"
#include "Number.hpp"

namespace ssd {

    class GameManager {
    public:
        GameManager(const NumberRange &, int);

        std::pair<int, int> getNumberBorders() const;

        int getLeftAttempts() const;

        bool checkQuestion(Questions, int);

    private:
        Number number;
        int leftAttempts;
    };

} // ssd namespace

#endif // GAME_MANAGER_HPP
