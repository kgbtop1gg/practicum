#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>
#include <memory>

class Coin {
private:
    float x, y;
    float radius;
    float speed;
    sf::CircleShape body;
    std::unique_ptr<sf::Shape> insideShape;
    int scoreReward;
    bool collected = false;
    sf::Clock jumpClock;

    void setRandomInsideShape();

public:
    Coin(float x, float y, float radius, float speed);

    void draw(sf::RenderWindow& window);
    void rotate(float deltaTime);
    void collect();
    int getScoreReward() const;
    bool isCollected() const;
    void reset(float newX, float newY);

    float getX() const;
    float getY() const;
    float getRadius() const;
};

#endif // COIN_H
