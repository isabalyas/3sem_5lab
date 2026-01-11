#include "Simulation.hpp"
#include <iostream>
#include <fstream>

int main() {
    createExampleInput();
    
    // Отладочный вывод input.txt
    std::cout << "Содержимое input.txt:" << std::endl;
    std::ifstream test("input.txt");
    std::string line;
    while (std::getline(test, line)) {
        std::cout << line << std::endl;
    }
    test.close();
    std::cout << std::endl;
    
    Simulation* simulation = nullptr;
    readInputFromFile("input.txt", simulation);
    
    if (!simulation) {
        std::cout << "Ошибка при создании симуляции." << std::endl;
        return 1;
    }
    
    std::cout << "Начало симуляции..." << std::endl;
    simulation->printCurrentState();
    
    simulation->runSimulation();
    
    std::cout << "\nФинальное состояние поля:" << std::endl;
    simulation->printFinalState();
    
    std::ofstream out("output.txt");
    std::streambuf* coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());
    
    simulation->printFinalState();
    
    std::cout.rdbuf(coutbuf);
    std::cout << "\nРезультат сохранен в output.txt" << std::endl;
    
    delete simulation;
    
    return 0;
}