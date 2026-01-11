#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "Animal.hpp"
#include <vector>
#include <string>

class Simulation {
private:
    int width, height, turns;
    std::vector<Animal*> animals;
    
public:
    Simulation(int w, int h, int t);
    ~Simulation();
    
    void addAnimal(Animal* animal);
    void runSimulation();
    void cleanupDeadAnimals();
    void printFinalState();
    void printCurrentState();
};

void readInputFromFile(const std::string& filename, Simulation*& sim);
void createExampleInput();

#endif