
#include <unistd.h>
#include <iostream>
#include "testAPI.hpp"

SnakeAPI::Direction TestAPI::computeDirection() const
{
    return SnakeAPI::Direction::Right;
}

void TestAPI::graphicalTic()
{
    printMap();
    usleep(250000);
}

void TestAPI::printMap(void) const
{
    auto &&map = getMap();

    for (auto i = 0; i < SnakeAPI::mapSize + 2; ++i)
        std::cout << '-';
    std::cout << std::endl;
    for (auto const &ee : map) {
        std::cout << '|';
        for (auto const &e : ee) {
            std::cout << e;
        }
        std::cout << '|' << std::endl;
    }
    for (auto i = 0; i < SnakeAPI::mapSize + 2; ++i)
        std::cout << '-';
    std::cout << std::endl;
}