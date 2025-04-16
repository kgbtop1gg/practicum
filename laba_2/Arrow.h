#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Tree; 

class Arrow {
public:
    Arrow(int startX, int startY, sf::Vector2f dir, int tileSize, int dmg, int speed);

    void move();
    bool hasReachedMaxDistance() const;
    void draw(sf::RenderWindow& window);
    bool checkCollisionWithTree(const Tree& tree) const;

    int getDamage() const;
    float getX() const;
    float getY() const;

private:
    sf::ConvexShape arrowShape;
    sf::Vector2f direction;
    sf::Vector2f position;
    sf::Vector2f startPosition;
    int maxDistance;
    int damage;
    int speed;
};

#endif // ARROW_H
