#ifndef ARCHER_H
#define ARCHER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Arrow.h" 
#include "Bomb.h"  
#include "Tree.h"
#include "Coin.h"   
#include "TileType.h"

class Bat;
class Witch;


class Archer {
private:
    sf::RectangleShape body;
    sf::Clock damageClock;  
    bool isDamaged = false; 
    sf::ConvexShape hat;
    sf::ConvexShape bow;
    sf::CircleShape leftEye;
    sf::CircleShape rightEye;
    sf::Vector2i position;
    int direction;
    int health;
    int attackDamage;
    std::vector<Arrow> arrows;
    sf::RectangleShape healthBar;          
    sf::RectangleShape missingHealthBar;   
    bool isHealed = false;
    sf::Clock healClock;

public:
    Archer(int startX, int startY, int direction);
    void updateGraphics();
    void attack(float tileSize);
    void moveArrows(std::vector<Bomb>& bombs, std::vector<Bat>& bats, std::vector<Witch>& Witches, std::vector<Tree>& trees);
    void checkCollisionWithBomb(std::vector<Bomb>& bombs);
    void checkCollisionWithCoins(std::vector<Coin>& coins);
    void move(int dx, int dy, const std::vector<std::vector<TileType>>& map, std::vector<Tree>& trees, std::vector<Coin>& coins);
    void update(sf::RenderWindow& window, std::vector<Bomb>& bombs, std::vector<Bat>& bats, std::vector<Witch>& Witches, std::vector<Tree>& trees, std::vector<Coin>& coins, bool& gameOver);
    void draw(std::vector<Tree>& trees, sf::RenderWindow& window);
    void takeDamage(int damage);
    bool isAlive() const;
    sf::Vector2i getPosition() const;
    void heal(int amount);
};

#endif // ARCHER_H
