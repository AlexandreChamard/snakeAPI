#include <cstring>
#include <iostream>
#include "genetic.h"

std::size_t gen::MDP_LENGTH = 1;
std::string FULL_CHARACTERS;

char gen::getCharacter(char c)
{
    //if (c == 0 || rand() % 1000 < gen::MUTATE_PERCENT)
    if (c == 0)
        return FULL_CHARACTERS[rand() % FULL_CHARACTERS.length()];
    return c;
}

gen::buffers_t gen::createFirstGen()
{
    for (char c = ' '; c < '~'; ++c) {
        FULL_CHARACTERS.push_back(c);
    }

    gen::buffers_t arr;

    std::srand(time(nullptr));
    for (auto &buff : arr) {
        buff.resize(gen::MDP_LENGTH);
        for (std::size_t i = 0; i < gen::MDP_LENGTH; ++i)
            buff[i] = getCharacter();
    }
    return arr;
}

gen::fitnesses_t gen::calcFitness(gen::buffers_t const &arr, std::function<fitness_t (buffer_t const &)> f)
{
    gen::fitnesses_t fit;

    for (std::size_t i = 0; i < arr.size(); ++i) {
        fit[i] = f(arr[i]);
    }
    return fit;
}

gen::fitness_t gen::getTotalFitness(gen::fitnesses_t const &fit)
{
    gen::fitness_t totalFit = 0;

    for (auto const &e : fit) {
        totalFit += e;
    }
    return totalFit;
}

gen::buffers_t gen::getNextGen(gen::buffers_t const &arr, gen::fitnesses_t fit)
{
    static int seed = time(nullptr);
    std::srand(seed);
    ++seed;
    gen::fitness_t totalFitness = getTotalFitness(fit);
    gen::buffers_t nextGen;
    auto it = nextGen.begin();

    while (it != nextGen.end()) {
        auto p1 = getRandomGuy(arr, fit, totalFitness);
        // totalFitness -= fit[p1];
        // fit[p1] = 0;
        auto p2 = getRandomGuy(arr, fit, totalFitness);
        // totalFitness -= fit[p2];
        // fit[p2] = 0;
        it = faireDesEnfants(it, arr[p1], arr[p2]);
    }
    return nextGen;
}

std::size_t gen::getRandomGuy(gen::buffers_t const &arr, gen::fitnesses_t const &fit, gen::fitness_t maxFitness)
{
    std::int64_t actFit = std::rand() % maxFitness;
    size_t i = 0;

    while (1) {
        if (fit[i] > 0) {
            actFit -= fit[i];
            if (actFit <= 0)
                return i;
        }
        ++i;
    }
}

gen::buffers_t::iterator gen::faireDesEnfants(gen::buffers_t::iterator it1, gen::buffer_t const &child1, gen::buffer_t const &child2)
{
    auto it2 = it1 + 1;

    size_t cut = std::rand() % MDP_LENGTH;

    it1->resize(gen::MDP_LENGTH);
    it2->resize(gen::MDP_LENGTH);
    size_t i = 0;
    while (i < cut) {
        (*it1)[i] = gen::getCharacter(child1[i]);
        (*it2)[i] = gen::getCharacter(child2[i]);
        ++i;
    }
    while (i < MDP_LENGTH) {
        (*it1)[i] = gen::getCharacter(child2[i]);
        (*it2)[i] = gen::getCharacter(child1[i]);
        ++i;
    }
    if (std::rand() % 100 < gen::MUTATE_PERCENT)
        (*it1)[std::rand() % MDP_LENGTH] = gen::getCharacter();
    if (std::rand() % 100 < gen::MUTATE_PERCENT)
        (*it2)[std::rand() % MDP_LENGTH] = gen::getCharacter();
    return it2 + 1;
}

std::pair<gen::buffer_t, gen::fitness_t> gen::getBestGuy(gen::buffers_t const &buffs, gen::fitnesses_t const &fit)
{
    std::size_t imax = 0;

    for (std::size_t i = 0; i < gen::NB_PEOPLE; ++i) {
        if (fit[i] > fit[imax]) {
            imax = i;
        }
    }
    return std::make_pair(buffs[imax], fit[imax]);
}

/*
récupérer toutes les lignes
pour chaque ligne :
    si l'état est diférent de 'fini' :
        si l'état est 'non modifié' :
            changer l'état à 'en cours'
            mettre la date de début

        pour chaque fichier dont on a les droits :
            changer les droits du fichier
            si réussi :
                ajouter 1 dans la case 'élément fait'
            sinon :
                ajouter 1 dans la case 'élément error'
            ajouter 1 dans la case 'fichier total'

        changer les droits du dossier courant
        
        ajouter 1 dans la case 'dossier fait'
        changer l'état à 'fini'
        mettre la date de fin

*/