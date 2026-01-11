#include "Simulation.hpp"
#include "Rabbit.hpp"
#include "Wolf.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

Simulation::Simulation(int w, int h, int t) : width(w), height(h), turns(t) {}

Simulation::~Simulation() {
    for (auto animal : animals) {
        delete animal;
    }
}

void Simulation::addAnimal(Animal* animal) {
    animals.push_back(animal);
}

void Simulation::runSimulation() {
    for (int turn = 0; turn < turns; turn++) {
        // Движение
        for (auto animal : animals) {
            if (animal->alive()) {
                animal->move(width, height);
            }
        }
        
        // Питание
        for (auto animal : animals) {
            if (animal->alive() && animal->isPredator()) {
                animal->eat(animals);
            }
        }
        
        // Старение
        for (auto animal : animals) {
            if (animal->alive()) {
                animal->aging();
            }
        }
        
        // Размножение
        std::vector<Animal*> newborns;
        for (auto animal : animals) {
            if (animal->alive()) {
                animal->reproduce(newborns);
            }
        }
        
        // Добавляем новорожденных
        for (auto baby : newborns) {
            animals.push_back(baby);
        }
        
        // Проверка смерти
        for (auto animal : animals) {
            if (animal->alive()) {
                animal->checkDeath();
            }
        }
        
        // Очистка мертвых
        cleanupDeadAnimals();
    }
}

void Simulation::cleanupDeadAnimals() {
    std::vector<Animal*> aliveAnimals;
    for (auto animal : animals) {
        if (animal->alive()) {
            aliveAnimals.push_back(animal);
        } else {
            delete animal;
        }
    }
    animals = aliveAnimals;
}

void Simulation::printFinalState() {
    std::vector<std::vector<std::pair<int, int>>> field(height, 
        std::vector<std::pair<int, int>>(width, {0, 0}));
    
    for (auto animal : animals) {
        if (animal->alive()) {
            int x = animal->getX();
            int y = animal->getY();
            
            if (animal->isPredator()) {
                field[y][x].second++;
            } else {
                field[y][x].first++;
            }
        }
    }
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int preyCount = field[y][x].first;
            int predCount = field[y][x].second;
            
            if (preyCount == 0 && predCount == 0) {
                std::cout << "*";
            } else if (preyCount > 0) {
                std::cout << "+" << preyCount;
            } else if (predCount > 0) {
                std::cout << "-" << predCount;
            }
            
            if (x < width - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void Simulation::printCurrentState() {
    std::vector<std::vector<std::string>> field(height, 
        std::vector<std::string>(width, "."));
    
    for (auto animal : animals) {
        if (animal->alive()) {
            int x = animal->getX();
            int y = animal->getY();
            
            char symbol = animal->getSymbol();
            
            if (field[y][x] == ".") {
                field[y][x] = std::string(1, symbol);
            } 
            else if (field[y][x] == "R" || field[y][x] == "W") {
                if ((field[y][x] == "R" && symbol == 'W') || 
                    (field[y][x] == "W" && symbol == 'R')) {
                    field[y][x] = "X";
                }
                else {
                    field[y][x] = "2";
                }
            }
            else if (field[y][x] == "2") {
                field[y][x] = "3";
            }
        }
    }
    
    std::cout << "\nТекущее состояние поля:" << std::endl;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << field[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void readInputFromFile(const std::string& filename, Simulation*& sim) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Не могу открыть файл " << filename << std::endl;
        return;
    }
    
    int N, M, T, R, W;
    file >> N >> M >> T >> R >> W;
    
    sim = new Simulation(N, M, T);
    
    for (int i = 0; i < R; i++) {
        int x, y, d, k;
        file >> x >> y >> d >> k;
        Rabbit* rabbit = new Rabbit(x, y, d, k);
        sim->addAnimal(rabbit);
    }
    
    for (int i = 0; i < W; i++) {
        int x, y, d, k;
        file >> x >> y >> d >> k;
        Wolf* wolf = new Wolf(x, y, d, k);
        sim->addAnimal(wolf);
    }
    
    file.close();
}

void createExampleInput() {
    std::ofstream file("input.txt");
    file << "3 3 3 2 1" << std::endl;
    file << "1 2 1 1" << std::endl;
    file << "1 1 1 1" << std::endl;
    file << "1 1 0 2" << std::endl;
    file.close();
    std::cout << "Создан пример входного файла input.txt" << std::endl;
}