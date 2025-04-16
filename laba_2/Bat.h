#ifndef BAT_H
#define BAT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "TileType.h"


class Archer;
class Witch;

class Bat {
private:
    sf::CircleShape body;
    sf::ConvexShape leftWing, rightWing;
    sf::ConvexShape leftEye, rightEye;
    sf::ConvexShape leftTooth, rightTooth;
    sf::Vector2f position;
    float radius;
    float wingLength;
    bool wingsUp;
    float speed;
    sf::Vector2f direction;
    sf::Clock attackClock;
    float attackSpeed;
    float attackRange;
    bool isAttacking;
    sf::Clock toothColorClock;
    sf::Clock damageClock;
    sf::Clock deathClock; 
    sf::CircleShape explosionEffect;
    std::vector<Bat> bats;
    int health;
    bool isDead;
    bool isVisibleAfterDeath; 
    void setHealth(int newHealth);

    void updateWings();

public:
    Bat(float x, float y, float r, float wingLen, float spd, float atkSpeed, float atkRange);

    void moveTowards(sf::Vector2f target, std::vector<Bat>& bats);
    void toggleWings();
    void attack(Archer& archer);
    void update(sf::Vector2f archerPosition, Archer& archer, std::vector<Bat>& bats);
    void draw(sf::RenderWindow& window);

    void takeDamage(int amount);
    
    void setIsDead(bool dead);
    bool getisdead() const;
    float getX() const;
    float getY() const;
    float getRadius() const;
    sf::Clock damageBlinkClock; 
    bool isBlinking = false;    
    sf::Time blinkDuration = sf::seconds(0.1f); 

    void respawn();
    void updateGraphics();
    void set_health(int a);
};
#endif
