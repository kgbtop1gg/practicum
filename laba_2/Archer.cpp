#include "Archer.h"
#include "Bat.h"
#include "Witch.h"
#include "Tree.h"
#include "TileType.h"
#include "Bomb.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <cstdlib>  
#include <ctime>    
#include <memory>

const int tileSize = 20;

Archer::Archer(int startX, int startY, int direction)
    : direction(direction), health(4500), attackDamage(3000) {
    position = { startX, startY };

    body.setSize(sf::Vector2f(tileSize, tileSize * 1.3));
    body.setFillColor(sf::Color::White);

    hat.setPointCount(4);
    hat.setFillColor(sf::Color(255, 215, 0));

    bow.setPointCount(3);
    bow.setOutlineColor(sf::Color::Yellow);
    bow.setOutlineThickness(2.f);
    bow.setFillColor(sf::Color::Transparent);

    leftEye.setRadius(tileSize / 10.f);
    leftEye.setFillColor(sf::Color::Black);
    rightEye.setRadius(tileSize / 10.f);
    rightEye.setFillColor(sf::Color::Black);

    healthBar.setSize(sf::Vector2f(4 * tileSize, tileSize));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition(10.f, 10.f);

    missingHealthBar.setSize(sf::Vector2f(4 * tileSize, tileSize));
    missingHealthBar.setFillColor(sf::Color::White);
    missingHealthBar.setPosition(10.f, 10.f);

    updateGraphics();
}

void Archer::updateGraphics() {
 
    if (!isAlive()) {

        body.setFillColor(sf::Color::White);


        body.setRotation(90);

        float centerX = body.getPosition().x;  
        float centerY = body.getPosition().y + tileSize / 2.f;  

        hat.setRotation(90);

        hat.setPosition(centerX - tileSize / 2.f, centerY - tileSize / 2.f); 
        hat.setPoint(0, sf::Vector2f(0.f, 0.f));  
        hat.setPoint(1, sf::Vector2f(tileSize, 0.f)); 
        hat.setPoint(2, sf::Vector2f(tileSize, tileSize));  
        hat.setPoint(3, sf::Vector2f(0.f, tileSize));  

        // Лук и глаза исчезают
        leftEye.setPosition(-100, -100);
        rightEye.setPosition(-100, -100);
        bow.setPoint(0, sf::Vector2f(-100, -100));
        bow.setPoint(1, sf::Vector2f(-100, -100));
        bow.setPoint(2, sf::Vector2f(-100, -100));

        healthBar.setSize(sf::Vector2f(4 * tileSize, tileSize / 2));
        healthBar.setFillColor(sf::Color::White);
        healthBar.setPosition(10.f, 10.f);
        missingHealthBar.setSize(sf::Vector2f(4 * tileSize, tileSize / 2));
        missingHealthBar.setFillColor(sf::Color::White);
        missingHealthBar.setPosition(10.f + healthBar.getSize().x, 10.f);

        return;
    }

   
    body.setPosition(position.x * tileSize, position.y * tileSize - tileSize / 2);

    float centerX = body.getPosition().x;
    float centerY = body.getPosition().y + tileSize / 2.f;

  
    if (hat.getRotation() == 0) {
        hat.setPosition(centerX - tileSize / 2.f, centerY - tileSize);  
        hat.setPoint(0, sf::Vector2f(0.f, 0.f));  
        hat.setPoint(1, sf::Vector2f(tileSize, 0.f)); 
        hat.setPoint(2, sf::Vector2f(tileSize, tileSize));  
        hat.setPoint(3, sf::Vector2f(0.f, tileSize)); 
    }
    else { // Поворот на 90 градусов
        hat.setRotation(90);
        hat.setPosition(centerX - tileSize / 2.f, centerY - tileSize / 2.f);
        hat.setPoint(0, sf::Vector2f(0.f, 0.f));  
        hat.setPoint(1, sf::Vector2f(tileSize, 0.f));
        hat.setPoint(2, sf::Vector2f(tileSize, tileSize));  
        hat.setPoint(3, sf::Vector2f(0.f, tileSize));  
    }

    // Лук
    bow.setPoint(0, sf::Vector2f(body.getPosition().x + tileSize, body.getPosition().y + tileSize - 2));
    bow.setPoint(1, sf::Vector2f(body.getPosition().x + 0.5 * tileSize, body.getPosition().y + tileSize / 1.3 + 0.5));
    bow.setPoint(2, sf::Vector2f(body.getPosition().x + 1.5 * tileSize, body.getPosition().y + tileSize / 1.3 + 0.5));

    // Глаза
    if (direction == 0) { // Вперёд
        leftEye.setPosition(body.getPosition().x + tileSize / 4.f, body.getPosition().y + tileSize / 4.f);
        rightEye.setPosition(body.getPosition().x + 3 * tileSize / 4.f, body.getPosition().y + tileSize / 4.f);
    }
    else if (direction == 1) { // Влево
        leftEye.setPosition(body.getPosition().x + tileSize / 4.f, body.getPosition().y + tileSize / 4.f);
        rightEye.setPosition(-100, -100);
    }
    else if (direction == 2) { // Вправо
        leftEye.setPosition(-100, -100);
        rightEye.setPosition(body.getPosition().x + 3 * tileSize / 4.f, body.getPosition().y + tileSize / 4.f);
    }
    else if (direction == 3) { // Назад
        leftEye.setPosition(-100, -100);
        rightEye.setPosition(-100, -100);
    }

 
    float healthPercentage = static_cast<float>(health) / 4500.0f;
    healthPercentage = std::max(0.f, std::min(1.f, healthPercentage));
    healthBar.setSize(sf::Vector2f(4 * tileSize * healthPercentage, tileSize / 2));
    healthBar.setPosition(10.f, 10.f);
    missingHealthBar.setSize(sf::Vector2f(4 * tileSize * (1 - healthPercentage), tileSize / 2));
    missingHealthBar.setPosition(10.f + healthBar.getSize().x, 10.f);

    if (isHealed) {
        if (healClock.getElapsedTime().asSeconds() >= 0.2f) {
            body.setFillColor(sf::Color::White);
            isHealed = false;
        }
        else {
            body.setFillColor(sf::Color::Green);
        }
    }
    else if (isDamaged) {
        if (damageClock.getElapsedTime().asSeconds() >= 0.2f) {
            body.setFillColor(sf::Color::White);
            isDamaged = false;
        }
        else {
            body.setFillColor(sf::Color::Red);
        }
    }
    else {
        body.setFillColor(sf::Color::White);
    }

    hat.setFillColor(sf::Color(255, 215, 0)); 
    bow.setOutlineColor(sf::Color::Yellow);   
}


void Archer::attack(float tileSize) {
    sf::Vector2f dir(0.f, 0.f);
    switch (direction) {
    case 0: dir = sf::Vector2f(0.f, 1.f); break;
    case 1: dir = sf::Vector2f(-1.f, 0.f); break;
    case 2: dir = sf::Vector2f(1.f, 0.f); break;
    case 3: dir = sf::Vector2f(0.f, -1.f); break;
    }
    arrows.emplace_back(position.x * tileSize + tileSize / 2, position.y * tileSize + tileSize / 2, dir, tileSize, attackDamage, 10);
}

void Archer::moveArrows(std::vector<Bomb>& bombs, std::vector<Bat>& bats, std::vector<Witch>& witches, std::vector<Tree>& trees) {
    for (auto arrow = arrows.begin(); arrow != arrows.end();) {
        arrow->move();
        float arrowX = arrow->getX();
        float arrowY = arrow->getY();

        bool arrowErased = false;

        for (auto& bomb : bombs) {
            float bombCenterX = bomb.getX() + bomb.getRadius();
            float bombCenterY = bomb.getY() + bomb.getRadius();

            float dx = arrowX - bombCenterX;
            float dy = arrowY - bombCenterY;
            float distance = std::sqrt(dx * dx + dy * dy) - 4;

            if (distance <= bomb.getRadius()) {
                if (!bomb.isExploded()) {
                    bomb.takeDamage(attackDamage);
                    arrow = arrows.erase(arrow);
                    arrowErased = true;
                    break;
                }
            }
        }
        if (arrowErased) continue;

        if (arrow->hasReachedMaxDistance()) {
            arrow = arrows.erase(arrow);
            continue;
        }

        for (auto& bat : bats) {
            float batCenterX = bat.getX();
            float batCenterY = bat.getY();

            float dx = arrowX - batCenterX;
            float dy = arrowY - batCenterY;
            float distance = std::sqrt(dx * dx + dy * dy) - 4;

            if (distance <= bat.getRadius() && !bat.getisdead()) {
                bat.takeDamage(500);
                arrow = arrows.erase(arrow);
                arrowErased = true;
                break;
            }
        }
        if (arrowErased) continue;

        for (auto& witch : witches) {
            if (witch.isAlive()) {
                float witchCenterX = witch.getX() * tileSize + witch.getWidth() / 2;
                float witchCenterY = witch.getY() * tileSize + witch.getHeight() / 2;

                float dx = arrowX - witchCenterX;
                float dy = arrowY - witchCenterY;
                float distance = std::sqrt(dx * dx + dy * dy);

                float witchHitRadius = std::max(witch.getWidth(), witch.getHeight()) / 2;
                if (distance <= witchHitRadius) {
                    witch.takeDamage(attackDamage);
                    arrow = arrows.erase(arrow);
                    arrowErased = true;
                    break;
                }
            }
        }
        if (arrowErased) continue;

        for (auto& tree : trees) {
            if (arrow->checkCollisionWithTree(tree)) {
                arrow = arrows.erase(arrow);
                arrowErased = true;
                break;
            }
        }

        if (!arrowErased)
            ++arrow;
    }
}


void Archer::checkCollisionWithBomb(std::vector<Bomb>& bombs) {
    float archerCenterX = position.x * tileSize + tileSize / 2;
    float archerCenterY = position.y * tileSize + tileSize / 2;

    for (auto& bomb : bombs) {
        float bombCenterX = bomb.getX() + bomb.getRadius();
        float bombCenterY = bomb.getY() + bomb.getRadius();

        float dxBomb = archerCenterX - bombCenterX;
        float dyBomb = archerCenterY - bombCenterY;
        float distance = std::sqrt(dxBomb * dxBomb + dyBomb * dyBomb);

        if (distance <= bomb.getRadius() && !bomb.isExploded()) {
            bomb.triggerExplosion(); 
            takeDamage(100);        
        }
    }
}


void Archer::checkCollisionWithCoins(std::vector<Coin>& coins) {
    float archerCenterX = position.x * tileSize + tileSize / 2;
    float archerCenterY = position.y * tileSize + tileSize / 2;

    for (Coin& coin : coins) {
        float coinCenterX = coin.getX();
        float coinCenterY = coin.getY();

        float dx = archerCenterX - coinCenterX;
        float dy = archerCenterY - coinCenterY;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= coin.getRadius() && !coin.isCollected()) {
            coin.collect();
        }
    }
}

void Archer::move(int dx, int dy, const std::vector<std::vector<TileType>>& map, std::vector<Tree>& trees, std::vector<Coin>& coins) {
    if (!isAlive()) return;

    int mapWidth = map[0].size();  
    int mapHeight = map.size();   

    int newX = position.x + dx;
    int newY = position.y + dy;


    if (newX < 0 || newX >= mapWidth || newY < 0 || newY >= mapHeight) {
        return;  
    }

    
    if (map[newY][newX] == TileType::Water) {
        return;  
    }

   
    for (const Tree& tree : trees) {
        if (tree.isPathBlocked(newX * tileSize, newY * tileSize)) {
            return;  
        }
    }

    // Двигаем лучника
    position.x = newX;
    position.y = newY;

    if (dx == 0 && dy > 0) direction = 0;  // Вниз
    else if (dx < 0 && dy == 0) direction = 1;  // Влево
    else if (dx > 0 && dy == 0) direction = 2;  // Вправо
    else if (dx == 0 && dy < 0) direction = 3;  // Вверх

    updateGraphics();
}


void Archer::update(sf::RenderWindow& window, std::vector<Bomb>& bombs, std::vector<Bat>& bats, std::vector<Witch>& Witches, std::vector<Tree>& trees, std::vector<Coin>& coins, bool& gameOver) {
    moveArrows(bombs, bats, Witches, trees);
    checkCollisionWithBomb(bombs);
    updateGraphics(); 

    if (!isAlive()) {
        gameOver = false;
    }
}


void Archer::draw(std::vector<Tree>& trees, sf::RenderWindow& window) {
    if (!isAlive()) {
        
        body.setFillColor(sf::Color(255, 255, 255, 128)); 
        window.draw(body);
        window.draw(hat);
        window.draw(bow);
        window.draw(leftEye);
        window.draw(rightEye);
        for (auto& arrow : arrows) {
            arrow.draw(window); 
        }
        window.draw(healthBar); 
        window.draw(missingHealthBar);
        return; 
    }

    bool drawAboveTrees = false;

    for (const Tree& tree : trees) {
        int treeX = tree.get_tree_x();
        int treeY = tree.get_tree_y();

     
        if (position.x * tileSize >= treeX && position.x * tileSize < treeX + tileSize &&
            position.y * tileSize == treeY + tileSize) {
            drawAboveTrees = true;
            break;
        }
    }

    if (drawAboveTrees) {
      
        for (Tree& tree : trees) {
            tree.draw(window);
        }
        window.draw(body);
        window.draw(hat);
        window.draw(bow);
        window.draw(leftEye);
        window.draw(rightEye);
        for (auto& arrow : arrows) {
            arrow.draw(window);
        }
        window.draw(healthBar);
        window.draw(missingHealthBar);
    }
    else {
       
        window.draw(body);
        window.draw(hat);
        window.draw(bow);
        window.draw(leftEye);
        window.draw(rightEye);
        for (auto& arrow : arrows) {
            arrow.draw(window);
        }
        window.draw(healthBar);
        window.draw(missingHealthBar);
        for (Tree& tree : trees) {
            tree.draw(window);
        }
    }
}


void Archer::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;  
    isDamaged = true;
    damageClock.restart();
}


bool Archer::isAlive() const {
    return health > 0;
}

sf::Vector2i Archer::getPosition() const {
    return position;
}

void Archer::heal(int amount) {
    health += amount;
    if (health > 4500) {
        health = 4500;
    }

    isHealed = true;
    healClock.restart();
}