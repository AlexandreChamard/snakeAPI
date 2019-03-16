
#include <array>
#include <string>
#include <algorithm>
#include <functional>

namespace gen {

extern std::size_t MDP_LENGTH;

constexpr auto CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

constexpr int MUTATE_PERCENT = 10; // percent / 1000
constexpr std::size_t NB_PEOPLE = 3000;

using buffer_t = std::string;
using buffers_t = std::array<buffer_t, NB_PEOPLE>;
using fitness_t = uint32_t;
using fitnesses_t = std::array<fitness_t, NB_PEOPLE>;

buffers_t createFirstGen(void);
fitnesses_t calcFitness(buffers_t const &, std::function<fitness_t (buffer_t const &)>);

fitness_t getTotalFitness(fitnesses_t const &);
buffers_t getNextGen(buffers_t const &, fitnesses_t);

char getCharacter(char = 0);

std::size_t getRandomGuy(buffers_t const &, fitnesses_t const &, fitness_t);
buffers_t::iterator faireDesEnfants(buffers_t::iterator, buffer_t const &, buffer_t const &);

std::pair<buffer_t, fitness_t> getBestGuy(buffers_t const &, fitnesses_t const &);

}