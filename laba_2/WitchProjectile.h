#ifndef WITCHPROJECTILE_H
#define WITCHPROJECTILE_H

#include <SFML/Graphics.hpp>
#include "Archer.h"

class WitchProjectile {
private:
    float x, y; 
    float radius; 
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed;
    bool active;
    
public:
    WitchProjectile(float startX, float startY, float targetX, float targetY, float speed);
    void update(Archer& archer, const std::vector<Tree>& trees);
    void draw(sf::RenderWindow& window);
    bool isActive() const { return active; }
    bool checkCollision(Archer& archer);
    void deactivate() { active = false; }

    // Геттеры
    float getX() const;
    float getY() const;
    float getRadius() const;

    // Сеттеры
    void setX(float newX);
    void setY(float newY);
    void setRadius(float newRadius);
};

#endif