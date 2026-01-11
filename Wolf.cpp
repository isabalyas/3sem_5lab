#include "Wolf.hpp"

Wolf::Wolf() : Animal() {
    maxAge = 50;
    mealsEaten = 0;
    mealsToReproduce = 2;
}

Wolf::Wolf(int x1, int y1, int d1, int k1) 
    : Animal(x1, y1, d1, k1, 50), mealsEaten(0), mealsToReproduce(2) {}

void Wolf::move(int width, int height) {
    if (!isAlive) return;
    
    for (int i = 0; i < 2; i++) {
        switch (d) {
            case UP:    updatePosition(0, -1, width, height); break;
            case RIGHT: updatePosition(1, 0, width, height); break;
            case DOWN:  updatePosition(0, 1, width, height); break;
            case LEFT:  updatePosition(-1, 0, width, height); break;
        }
    }
    
    moveCount++;
    if (k > 0 && moveCount >= k) {
        changeDirection();
    }
}

void Wolf::eat(std::vector<Animal*>& animals) {
    if (!isAlive) return;
    
    for (auto& animal : animals) {
        if (animal != this && animal->alive() && !animal->isPredator() &&
            animal->getX() == x && animal->getY() == y) {
            mealsEaten++;
            animal = nullptr;
        }
    }
}

void Wolf::reproduce(std::vector<Animal*>& animals) {
    if (!isAlive) return;
    
    if (mealsEaten >= mealsToReproduce) {
        Wolf* baby = new Wolf(x, y, d, k);
        animals.push_back(baby);
        mealsEaten = 0;
    }
}

void Wolf::checkDeath() {
    if (age >= maxAge) {
        isAlive = false;
    }
}

char Wolf::getSymbol() const { return 'W'; }
bool Wolf::isPredator() const { return true; }
int Wolf::getMealsEaten() const { return mealsEaten; }