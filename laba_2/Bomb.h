#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <ctime>   
class Bomb {
private:
    float x, y;
    float radius;
    sf::CircleShape body;
    sf::CircleShape leftEye;
    sf::CircleShape rightEye;
    sf::RectangleShape fuse;
    sf::CircleShape fuseTip;
    int health;

    bool exploded;
    sf::Clock explosionTimer;
    sf::CircleShape explosionEffect;

public:
    Bomb(float x, float y, int tileSize);

    void draw(sf::RenderWindow& window);
    void takeDamage(int damage);
    void triggerExplosion();
    void update(float tileSize);
    void respawn(int tileSize);
    void increaseSize();

    bool isExploded() const;
    float getX() const;
    float getY() const;
    float getRadius() const;

private:
    void updateGraphics(int tileSize);
};

#endif // BOMB_H


