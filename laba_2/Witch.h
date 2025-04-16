#ifndef WITCH_H
#define WITCH_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "WitchProjectile.h"

#include "TileType.h"
#include "Tree.h"

class Archer;
class Bat;

class Witch {
private:
    sf::Vector2f position;
    int health;
    int width, height;
    float speed;
    int attackPower;
    sf::Clock attackClock;
    sf::Clock moveClock;
    sf::Vector2i direction;
    std::vector<WitchProjectile> projectiles;
    std::vector<Bat> bats;
    bool wingsUp;
    sf::RectangleShape upperBody, lowerBody, staff, staffCross, arm;
    sf::ConvexShape hat;
    sf::CircleShape leftEye, rightEye;
    bool isDead;
    float deathTimer;
    bool isVisible;
    float attackCooldown; 
    float attackRate;     
    void updateGraphics();
    float spawnCooldown = 5.0f; 
public:
    Witch(int startX, int startY, int width, int height, float speed, int attackPower);
    void attack(sf::Vector2f target);
    void update(sf::Vector2f archerPosition, Archer& archer, float deltaTime, const std::vector<std::vector<TileType>>& map, const std::vector<Tree>& trees);
    void move(sf::Vector2f target, const std::vector<std::vector<TileType>>& map, const std::vector<Tree>& trees);
    void draw(sf::RenderWindow& window, const std::vector<Tree>& trees);
    void takeDamage(int damage);
    bool isAlive() const;
    void spawnBats();
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    int getHealth() const;
    bool is_Dead() const;
    bool is_Visible() const;
    void setHealth(int a);
};

#endif
