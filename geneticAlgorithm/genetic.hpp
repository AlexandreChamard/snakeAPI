
#include <vector>
#include <memory>

template<class T, typename Fitness = uint64_t>
class GeneticAPI {
public:
    using DataPtr    = std::shared_ptr<T>;
    using Generation = std::vector<DataPtr>;

    inline GeneticAPI(unsigned int peoplePerGen = 1000, double mutatePercent = 0.05);
    virtual ~GeneticAPI(void);

    inline void run(unsigned long n = 1);

    virtual void getFitness(DataPtr, Fitness &) = 0;
    virtual void createNewGuys(DataPtr child1, DataPtr child2, DataPtr const parent1, DataPtr const parent2) = 0;

private:
    unsigned int            peoplePerGen;
    double                  mutatePercent;

    Generation              generation;
    std::vector<Fitness>    fitness;

private:
    inline void createFirstGeneration(void);
    inline void getNextGeneration(void);

    inline Fitness getTotalFitness(void);

    inline typename Generation::iterator getRandomGuy(void);
};

template<class T, typename Fitness>
GeneticAPI<T, Fitness>::GeneticAPI(unsigned int peoplePerGen, double mutatePercent):
peoplePerGen{peoplePerGen},
mutatePercent{mutatePercent}
{}

template<class T, typename Fitness>
void GeneticAPI<T, Fitness>::run(unsigned long n)
{
}

template<class T, typename Fitness>
void GeneticAPI<T, Fitness>::createFirstGeneration()
{
}

template<class T, typename Fitness>
void GeneticAPI<T, Fitness>::getNextGeneration()
{
}

template<class T, typename Fitness>
Fitness GeneticAPI<T, Fitness>::getTotalFitness()
{
}

template<class T, typename Fitness>
typename GeneticAPI<T, Fitness>::Generation::iterator GeneticAPI<T, Fitness>::getRandomGuy()
{
}