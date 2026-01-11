#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <vector>

enum Direction { UP, RIGHT, DOWN, LEFT };

class Animal {
protected:
    int x, y;
    Direction d;
    int k;
    int age;
    int moveCount;
    int maxAge;
    bool isAlive;
    
public:
    Animal();
    Animal(int x1, int y1, int d1, int k1, int maxAge);
    virtual ~Animal();
    
    int getX() const;
    int getY() const;
    int getAge() const;
    bool alive() const;
    
    virtual void move(int width, int height) = 0;
    virtual void eat(std::vector<Animal*>& animals) = 0;
    virtual void reproduce(std::vector<Animal*>& animals) = 0;
    virtual void checkDeath() = 0;
    virtual char getSymbol() const = 0;
    virtual bool isPredator() const = 0;
    
    void aging();
    void updatePosition(int dx, int dy, int width, int height);
    void changeDirection();
};

#endif