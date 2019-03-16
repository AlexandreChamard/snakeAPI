#include "snakeAPI.hpp"


class TestAPI : public SnakeAPI {
private:
    Direction computeDirection() const override;

    void graphicalTic() override;

    void printMap(void) const;
};
