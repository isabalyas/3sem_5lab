#ifndef RABBIT_HPP
#define RABBIT_HPP

#include "Animal.hpp"

class Rabbit : public Animal {
private:
    int mealsEaten;
    int reproductionAge1;
    int reproductionAge2;
    bool reproducedAtAge1;
    bool reproducedAtAge2;
    
public:
    Rabbit();
    Rabbit(int x1, int y1, int d1, int k1);
    
    void move(int width, int height) override;
    void eat(std::vector<Animal*>& animals) override;
    void reproduce(std::vector<Animal*>& animals) override;
    void checkDeath() override;
    char getSymbol() const override;
    bool isPredator() const override;
};

#endif