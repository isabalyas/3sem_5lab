#include "Animal.hpp"

Animal::Animal() : x(0), y(0), d(UP), k(1), age(0), moveCount(0), maxAge(50), isAlive(true) {}

Animal::Animal(int x1, int y1, int d1, int k1, int maxAge) 
    : x(x1), y(y1), d(static_cast<Direction>(d1)), k(k1), age(0), 
      moveCount(0), maxAge(maxAge), isAlive(true) {}

Animal::~Animal() {}

int Animal::getX() const { return x; }
int Animal::getY() const { return y; }
int Animal::getAge() const { return age; }
bool Animal::alive() const { return isAlive; }

void Animal::aging() {
    if (isAlive) {
        age++;
    }
}

void Animal::updatePosition(int dx, int dy, int width, int height) {
    x = (x + dx + width) % width;
    y = (y + dy + height) % height;
}

void Animal::changeDirection() {
    d = static_cast<Direction>((d + 1) % 4);
    moveCount = 0;
}