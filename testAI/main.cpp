
#include <memory>
#include "testAPI.hpp"

int main()
{
    std::unique_ptr<SnakeAPI> api = std::make_unique<TestAPI>();

    api->run();
}