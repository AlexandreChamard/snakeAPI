
#include <vector>
#include <array>
#include <random>
#include <iterator>
#include <cstring>

class SnakeAPI {
public:
    virtual ~SnakeAPI() = default;

    enum class Direction {Up, Down, Left, Right};

    static constexpr char apple = 'A';
    static constexpr char snake = 'S';
    static constexpr char nothing = ' ';

    using posUnit_t = std::size_t;
    static constexpr posUnit_t mapSize = 50;
    using pos_t = std::pair<posUnit_t, posUnit_t>; // (x, y) 
    using map_t = std::array<std::array<char, mapSize>, mapSize>;

    inline uint64_t run(void); // return the points

    inline uint64_t getPoints(void) const {return _points;}

protected:

    virtual Direction computeDirection() const = 0;
    virtual void graphicalTic() = 0;

    inline map_t const &getMap(void) const {return _map;}
    inline pos_t const &getApplePos(void) const {return _applePos;}
    inline pos_t const &getHeadPos(void) const {return _snake[0];}

private:
    map_t                                   _map;
    std::vector<pos_t>                      _snake;
    pos_t                                   _applePos;
    uint64_t                                _points;
    bool                                    _end;

private:
    inline void generateMap(void);
    inline bool generateNewApple(void);
    inline bool nextTic(Direction);
};

std::size_t SnakeAPI::run(void)
{
    // Direction dir;
    

    generateMap();

    do {
        graphicalTic(); // if you don't want to have graphical print, just do an empty function.
    } while (nextTic(computeDirection()));
    return _points;
}

bool SnakeAPI::nextTic(Direction dir)
{
    auto nPos = _snake[0];

    switch (dir) {
        case Direction::Up:
            if (nPos.second-- == 0)
                return false;
            break;
        case Direction::Down: 
            if (nPos.second++ == mapSize - 1)
                return false;
            break;
        case Direction::Left:
            if (nPos.first-- == 0)
                return false;
            break;
        case Direction::Right:
            if (nPos.first++ == mapSize - 1)
                return false;
            break;
    }
    if (_map[nPos.second][nPos.first] == snake) {
        return false;
    }
    if (_map[nPos.second][nPos.first] == apple) {
        if (generateNewApple() == false)
            return false;
        _snake.push_back(_snake.back());
        ++_points;
    }
    _map[_snake.back().second][_snake.back().first] = nothing;
    std::memmove(_snake.data() + 1, _snake.data(), (_snake.size() - 1) * sizeof(_snake[0]));
    _snake[0] = nPos;
    _map[nPos.second][nPos.first] = snake;
    return true;
}

void SnakeAPI::generateMap(void)
{
    for (posUnit_t y = 0; y < mapSize; ++y) {
        for (posUnit_t x = 0; x < mapSize; ++x) {
            _map[y][x] = nothing;
        }
    }
    _map[mapSize / 2][mapSize / 2 + 1] = snake;
    _map[mapSize / 2][mapSize / 2] = snake;
    _map[mapSize / 2][mapSize / 2 - 1] = snake;
    _snake.push_back(std::make_pair(mapSize / 2 + 1, mapSize / 2));
    _snake.push_back(std::make_pair(mapSize / 2, mapSize / 2));
    _snake.push_back(std::make_pair(mapSize / 2 - 1, mapSize / 2));
    generateNewApple();
}

bool SnakeAPI::generateNewApple(void)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::vector<pos_t> allPos;

    for (posUnit_t y = 0; y < mapSize; ++y) {
        for (posUnit_t x = 0; x < mapSize; ++x) {
            if (_map[y][x] == nothing)
                allPos.push_back(std::make_pair(x, y));
        }
    }
    if (allPos.size() == 0) {
        return false;
    }
    auto it = allPos.begin();
    std::uniform_int_distribution<> dis(0, std::distance(it, allPos.end()) - 1);
    std::advance(it, dis(gen));
    _map[it->second][it->first] = apple;
    _applePos = *it;
    return true;
}
