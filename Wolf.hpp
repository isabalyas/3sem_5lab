#ifndef WOLF_HPP
#define WOLF_HPP

#include "Animal.hpp"

class Wolf : public Animal {
private:
    int mealsEaten;
    int mealsToReproduce;
    
public:
    Wolf();
    Wolf(int x1, int y1, int d1, int k1);
    
    void move(int width, int height) override;
    void eat(std::vector<Animal*>& animals) override;
    void reproduce(std::vector<Animal*>& animals) override;
    void checkDeath() override;
    char getSymbol() const override;
    bool isPredator() const override;
    
    int getMealsEaten() const;
};

#endif