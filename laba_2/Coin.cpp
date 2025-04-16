#include "Coin.h"

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <cstdlib>  
#include <ctime>    
#include <memory>

const int tileSize = 60;

Coin::Coin(float x, float y, float radius, float speed)
    : x(x), y(y), radius(radius), speed(speed) {

    body.setRadius(radius);
    body.setFillColor(sf::Color::Yellow);
    body.setPosition(x, y);

    setRandomInsideShape();
}

void Coin::draw(sf::RenderWindow& window) {
    if (collected) {
        if (jumpClock.getElapsedTime().asSeconds() < 0.5f) {
            body.setPosition(x, y - 10.f);
        }
        else {
            body.setPosition(x, y);
        }
    }
    window.draw(body);
    if (insideShape) {
        window.draw(*insideShape);
    }
}

void Coin::rotate(float deltaTime) {
    if (!collected) {
        body.setRotation(body.getRotation() + speed * deltaTime);
    }
}

void Coin::collect() {
    if (!collected) {
        collected = true;
        jumpClock.restart();
    }
}

int Coin::getScoreReward() const {
    return scoreReward;
}

bool Coin::isCollected() const {
    return collected;
}

void Coin::reset(float newX, float newY) {
    x = newX;
    y = newY;
    body.setPosition(x, y);
    collected = false;
    setRandomInsideShape();
}

float Coin::getX() const {
    return x;
}

float Coin::getY() const {
    return y;
}

float Coin::getRadius() const {
    return radius;
}

void Coin::setRandomInsideShape() {
    insideShape.reset();

    int random = rand() % 100;
    if (random < 70) {
        insideShape = std::make_unique<sf::CircleShape>(10.f);
        insideShape->setFillColor(sf::Color::Green);
        scoreReward = 100;
    }
    else if (random < 75) {
        insideShape = std::make_unique<sf::RectangleShape>(sf::Vector2f(15.f, 15.f));
        insideShape->setFillColor(sf::Color::Blue);
        scoreReward = 1000;
    }
    else {
        insideShape = std::make_unique<sf::CircleShape>(10.f);
        insideShape->setFillColor(sf::Color::White);
        scoreReward = 500;
    }

    insideShape->setOrigin(insideShape->getLocalBounds().width / 2.f, insideShape->getLocalBounds().height / 2.f);
    insideShape->setPosition(x + radius, y + radius);
}

