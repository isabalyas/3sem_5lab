#include "Rabbit.hpp"

Rabbit::Rabbit() : Animal() {
    maxAge = 30;
    mealsEaten = 0;
    reproductionAge1 = 5;
    reproductionAge2 = 10;
    reproducedAtAge1 = false;
    reproducedAtAge2 = false;
}

Rabbit::Rabbit(int x1, int y1, int d1, int k1) 
    : Animal(x1, y1, d1, k1, 30), mealsEaten(0), 
      reproductionAge1(5), reproductionAge2(10),
      reproducedAtAge1(false), reproducedAtAge2(false) {}

void Rabbit::move(int width, int height) {
    if (!isAlive) return;
    
    switch (d) {
        case UP:    updatePosition(0, -1, width, height); break;
        case RIGHT: updatePosition(1, 0, width, height); break;
        case DOWN:  updatePosition(0, 1, width, height); break;
        case LEFT:  updatePosition(-1, 0, width, height); break;
    }
    
    moveCount++;
    if (k > 0 && moveCount >= k) {
        changeDirection();
    }
}

void Rabbit::eat(std::vector<Animal*>& animals) {
    mealsEaten = 0;
}

void Rabbit::reproduce(std::vector<Animal*>& animals) {
    if (!isAlive) return;
    
    if ((age == reproductionAge1 && !reproducedAtAge1) || 
        (age == reproductionAge2 && !reproducedAtAge2)) {
        
        Rabbit* baby = new Rabbit(x, y, d, k);
        animals.push_back(baby);
        
        if (age == reproductionAge1) reproducedAtAge1 = true;
        if (age == reproductionAge2) reproducedAtAge2 = true;
    }
}

void Rabbit::checkDeath() {
    if (age >= maxAge) {
        isAlive = false;
    }
}

char Rabbit::getSymbol() const { return 'R'; }
bool Rabbit::isPredator() const { return false; }