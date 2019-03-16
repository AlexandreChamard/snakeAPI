
#include <iostream>
#include "genetic.h"

int main(int ac, char **av)
{
    if (ac == 1) {
        std::cout << "USAGE : " << *av << " mdp" << std::endl;
        return 1;
    }
    gen::buffer_t mdp(av[1]);
    gen::MDP_LENGTH = mdp.length();
    auto calcFit = [&mdp](gen::buffer_t const &buf){
        gen::fitness_t fit = 0;
        std::size_t pas = 1;
        for (std::size_t i = 0; i < gen::MDP_LENGTH; ++i) {
            if (mdp[i] == buf[i]) {
                fit += pas;
                pas += 1;
            }
        }
        return fit + 1;
    };

    auto gen = gen::createFirstGen();
    auto fit = gen::calcFitness(gen, calcFit);
    auto best = gen::getBestGuy(gen, fit);

    std::size_t gen_count = 0;
    while (best.first != mdp) {
        gen = gen::getNextGen(gen, fit);
        fit = gen::calcFitness(gen, calcFit);
        best = gen::getBestGuy(gen, fit);
        std::cout << "gen " << gen_count << " best : " << best.second << " " << best.first << std::endl;
        ++gen_count;
    }
}