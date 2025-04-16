#include "Bomb.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <cstdlib>  
#include <ctime>    
#include <memory>

const int tileSize = 60;

Bomb::Bomb(float x, float y, int tileSize)
    : x(x), y(y), exploded(false), health(1500) {

    radius = tileSize / 3.f;


    body.setRadius(radius);
    body.setFillColor(sf::Color::Black);
    body.setPosition(this->x, this->y);


    leftEye.setRadius(tileSize / 10.f);
    leftEye.setFillColor(sf::Color::Red);
    rightEye.setRadius(tileSize / 10.f);
    rightEye.setFillColor(sf::Color::Red);

   
    fuse.setSize(sf::Vector2f(2.f, tileSize / 2 - 1));
    fuse.setFillColor(sf::Color(169, 169, 169));

   
    fuseTip.setRadius(2.f);
    fuseTip.setFillColor(sf::Color::Red);


    explosionEffect.setFillColor(sf::Color::Red);
    explosionEffect.setRadius(0);
    explosionEffect.setOrigin(explosionEffect.getRadius(), explosionEffect.getRadius());

    updateGraphics(tileSize);
}

void Bomb::draw(sf::RenderWindow& window) {
    if (exploded) {
        window.draw(explosionEffect);
    }
    else {
        window.draw(body);
        window.draw(leftEye);
        window.draw(rightEye);
        window.draw(fuse);
        window.draw(fuseTip);
    }
}

void Bomb::takeDamage(int damage) {
    if (exploded) return;

    health -= damage;
    if (health <= 0) {
        triggerExplosion();
    }
}

void Bomb::triggerExplosion() {
    exploded = true;
    explosionTimer.restart();
    explosionEffect.setRadius(radius * 2.f);
    explosionEffect.setOrigin(explosionEffect.getRadius(), explosionEffect.getRadius());
    explosionEffect.setPosition(x + radius, y + radius);
}

void Bomb::update(float tileSize) {
    if (exploded && explosionTimer.getElapsedTime().asSeconds() > 1.0f) {
        explosionEffect.setRadius(0);
        respawn(tileSize);
    }
}

void Bomb::respawn(int tileSize) {
    exploded = false;
    float newX, newY;
    do {
        newX = (rand() % 10) * tileSize;
        newY = (rand() % 7) * tileSize;
    } while (newX == x && newY == y);

    x = newX;
    y = newY;
    radius = tileSize / 3.f;
    health = 1500;

    updateGraphics(tileSize);
}

void Bomb::increaseSize() {
    radius *= 1.5f;
    body.setRadius(radius);
    updateGraphics(static_cast<int>(radius * 3));
}

bool Bomb::isExploded() const {
    return exploded;
}

float Bomb::getX() const { return x; }
float Bomb::getY() const { return y; }
float Bomb::getRadius() const { return radius; }

void Bomb::updateGraphics(int tileSize) {
    body.setPosition(x, y);
    leftEye.setPosition(x + tileSize / 8, y + tileSize / 4.f);
    rightEye.setPosition(x + tileSize / 2.4, y + tileSize / 4.f);
    fuse.setPosition(x + tileSize / 3, y - tileSize / 2);

    fuseTip.setPosition(fuse.getPosition().x - 1, fuse.getPosition().y - 2);

    explosionEffect.setRadius(0);
    explosionEffect.setPosition(-100, -100);
}
