#include "Bat.h"
#include "Archer.h"
#include "Witch.h"
#include "TileType.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <cstdlib>  
#include <ctime>    
#include <memory>

const int tileSize = 20;

Bat::Bat(float x, float y, float r, float wingLen, float spd, float atkSpeed, float atkRange)
    : position(x, y), radius(r * 2 / 3), wingLength(wingLen), wingsUp(true), speed(spd),
    direction(0, 0), attackSpeed(atkSpeed), attackRange(atkRange), isAttacking(false), health(1000),
    isDead(false), isVisibleAfterDeath(false) {

    health = 10000;

    body.setRadius(radius);
    body.setFillColor(sf::Color(128, 0, 128));
    body.setOrigin(radius, radius);
    body.setPosition(position);

    leftEye.setPointCount(4);
    leftEye.setPoint(0, sf::Vector2f(-r / 2, -r / 4));
    leftEye.setPoint(1, sf::Vector2f(0, -r / 3));
    leftEye.setPoint(2, sf::Vector2f(r / 2, -r / 4));
    leftEye.setPoint(3, sf::Vector2f(0, 0));
    leftEye.setFillColor(sf::Color::Red);
    leftEye.setPosition(position.x - r / 5, position.y + r / 6);

    rightEye = leftEye;
    rightEye.setPosition(position.x + r / 5, position.y + r / 6);

    leftTooth.setPointCount(3);
    leftTooth.setPoint(0, sf::Vector2f(-r / 6, 0));
    leftTooth.setPoint(1, sf::Vector2f(0, r / 6));
    leftTooth.setPoint(2, sf::Vector2f(r / 6, 0));
    leftTooth.setFillColor(sf::Color::White);
    leftTooth.setPosition(position.x - r / 8, position.y + r / 2);

    rightTooth = leftTooth;
    rightTooth.setPosition(position.x + r / 8, position.y + r / 2);

    leftWing.setPointCount(4);
    rightWing.setPointCount(4);
    updateWings();
}

void Bat::set_health(int a) {
    health = a;
}

void Bat::updateWings() {
    float wingAngle = wingsUp ? -45.f : 45.f;

    leftWing.setPoint(0, sf::Vector2f(0, 0));
    leftWing.setPoint(1, sf::Vector2f(-wingLength, -wingLength / 3));
    leftWing.setPoint(2, sf::Vector2f(0, -wingLength * 2 / 3));
    leftWing.setPoint(3, sf::Vector2f(wingLength, -wingLength / 3));
    leftWing.setFillColor(sf::Color(128, 0, 128));
    leftWing.setPosition(position.x - radius, position.y);
    leftWing.setRotation(wingAngle);

    rightWing = leftWing;
    rightWing.setPosition(position.x + radius, position.y);
    rightWing.setRotation(-wingAngle);
}

void Bat::moveTowards(sf::Vector2f target, std::vector<Bat>& bats) {
    sf::Vector2f delta = target - position;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (distance < 1.5f * radius) return;

    if (!isDead) {
        direction = { delta.x / distance, delta.y / distance };

      
        sf::Vector2f newPosition = position + direction * speed;

        
        for (auto& otherBat : bats) {
            if (&otherBat == this || otherBat.getisdead()) continue; 

            float distToOther = std::sqrt(std::pow(newPosition.x - otherBat.getX(), 2) +
                std::pow(newPosition.y - otherBat.getY(), 2));
            if (distToOther < radius / 2 + 5) {
                return; 
            }
        }

      
        position = newPosition;

        body.setPosition(position);
        leftEye.setPosition(position.x - radius / 3, position.y + radius / 3);
        rightEye.setPosition(position.x + radius / 3, position.y + radius / 3);
        leftTooth.setPosition(position.x - radius / 6, position.y + radius / 2);
        rightTooth.setPosition(position.x + radius / 6, position.y + radius / 2);
        leftWing.setPosition(position.x - radius, position.y);
        rightWing.setPosition(position.x + radius, position.y);
    }
}



void Bat::toggleWings() {
    wingsUp = !wingsUp;
    updateWings();
}

void Bat::attack(Archer& archer) {
    if (isDead) return;

    if (attackClock.getElapsedTime().asSeconds() >= attackSpeed) {
        archer.takeDamage(750);
        attackClock.restart();

       
        isAttacking = true;
        toothColorClock.restart();
        leftTooth.setFillColor(sf::Color::Red);
        rightTooth.setFillColor(sf::Color::Red);
    }
}


float Bat::getX() const {
    return position.x;
}

float Bat::getY() const {
    return position.y;
}

float Bat::getRadius() const {
    return radius;
}

void Bat::setIsDead(bool dead) {
    isDead = dead;
    if (dead) {
        deathClock.restart(); 
        explosionEffect.setRadius(radius * 2); 
        explosionEffect.setPosition(position);
        isVisibleAfterDeath = true; 
    }
}

bool Bat::getisdead() const {
    return isDead;
}

void Bat::setHealth(int newHealth) {
    if (newHealth < 0) {
        health = 0;
        isDead = true;
    }
    else if (newHealth > 100) {
        health = 100;
    }
    else {
        health = newHealth;
    }

    if (health > 0) {
        isDead = false;
    }
}

void Bat::respawn() {
    isDead = false;
    float newX, newY;
    do {
        newX = (rand() % 10) * 60;
        newY = (rand() % 7) * 60;
    } while (newX == position.x && newY == position.y);

    position = { newX, newY };
    health = 1000;
    updateGraphics();
}

void Bat::updateGraphics() {
    
    if (isBlinking) {
        if (damageBlinkClock.getElapsedTime() < blinkDuration) {
            body.setFillColor(sf::Color::Black);
            leftEye.setFillColor(sf::Color::Black);
            rightEye.setFillColor(sf::Color::Black);
        }
        else {
          
            body.setFillColor(sf::Color(128, 0, 128));
            leftEye.setFillColor(sf::Color::Red);
            rightEye.setFillColor(sf::Color::Red);
            isBlinking = false;  
        }
    }

    
    if (isAttacking && toothColorClock.getElapsedTime().asSeconds() >= 1.0f) {
        leftTooth.setFillColor(sf::Color::White);
        rightTooth.setFillColor(sf::Color::White);
        isAttacking = false;  
    }

    body.setPosition(position);
    leftEye.setPosition(position.x - radius / 3, position.y + radius / 3);
    rightEye.setPosition(position.x + radius / 3, position.y + radius / 3);
    leftTooth.setPosition(position.x - radius / 6, position.y + radius / 2);
    rightTooth.setPosition(position.x + radius / 6, position.y + radius / 2);
    leftWing.setPosition(position.x - radius, position.y);
    rightWing.setPosition(position.x + radius, position.y);
}

void Bat::takeDamage(int amount) {
    if (isDead) return;

    health -= amount;
    damageClock.restart();  

    if (health <= 0) {
        isDead = true;
        deathClock.restart();
        leftTooth.setFillColor(sf::Color::Red);
        rightTooth.setFillColor(sf::Color::Red);
    }
    else {
        
        isBlinking = true;
        damageBlinkClock.restart(); 
    }
}

void Bat::update(sf::Vector2f archerPosition, Archer& archer, std::vector<Bat>& bats) {
    if (isDead) {
        if (deathClock.getElapsedTime().asSeconds() > 2.0f) {
            isVisibleAfterDeath = false;  
        }
        return;
    }

    moveTowards(archerPosition, bats);

    if (std::sqrt(std::pow(archerPosition.x - position.x, 2) +
        std::pow(archerPosition.y - position.y, 2)) <= attackRange) {
        attack(archer);
    }


    updateGraphics();
}

void Bat::draw(sf::RenderWindow& window) {
    if (isDead) {
      
        if (deathClock.getElapsedTime().asSeconds() <= 2.0f) {  
            leftTooth.setPosition(position.x - radius / 8, position.y + radius / 2);  
            window.draw(leftTooth);    
        }
        if (isVisibleAfterDeath) {
            window.draw(explosionEffect); 
        }
    }
    else {
        window.draw(body);  
        window.draw(leftWing);  
        window.draw(rightWing);  
        if (direction.y >= 0) {
            if (direction.x >= 0) {
                window.draw(rightEye);  
                window.draw(rightTooth);  
            }
            else {
                window.draw(leftEye);  
                window.draw(leftTooth);  
            }
        }
    }
}


