#include "Witch.h"
#include "Archer.h"
#include "WitchProjectile.h"
#include "Bat.h"
#include "Tree.h"

#include <cmath>

const int tileSize = 20;



Witch::Witch(int startX, int startY, int width, int height, float speed, int attackPower)
    : position(startX, startY), width(width * 0.6), height(height), speed(speed), attackPower(50),
    health(3000), wingsUp(true), isDead(false), deathTimer(0.f), isVisible(true) { 

    lowerBody.setSize(sf::Vector2f(width * 0.25, height / 3));
    lowerBody.setFillColor(sf::Color(128, 0, 128));
    upperBody.setSize(sf::Vector2f(width * 0.25, height / 3));
    upperBody.setFillColor(sf::Color::White);
    hat.setPointCount(3);
    hat.setFillColor(sf::Color(128, 0, 128));
    leftEye.setRadius(width / 30.f);
    leftEye.setFillColor(sf::Color::Black);
    rightEye.setRadius(width / 30.f);
    rightEye.setFillColor(sf::Color::Black);
    arm.setSize(sf::Vector2f(width, height));
    arm.setFillColor(sf::Color(128, 0, 128));
    staff.setSize(sf::Vector2f(width / 16, height));
    staff.setFillColor(sf::Color(139, 69, 19));
    staffCross.setSize(sf::Vector2f(width / 2, width / 10));
    staffCross.setFillColor(sf::Color(139, 69, 19));

    updateGraphics();
}

void Witch::updateGraphics() {
    float x = position.x * tileSize;
    float y = position.y * tileSize;

    if (isDead) {
    
        lowerBody.setPosition(x, y);
        upperBody.setPosition(x - tileSize + 20, y);

      
        lowerBody.setRotation(90);
        upperBody.setRotation(90);

        hat.setPoint(0, sf::Vector2f(x - tileSize - tileSize + 8, y + tileSize / 2 - 8));        
        hat.setPoint(1, sf::Vector2f(x + width - 2 * tileSize - 6, y + tileSize + 2));  
        hat.setPoint(2, sf::Vector2f(x + width - 2 * tileSize - 6, y - 12)); 

    
        leftEye.setPosition(-1000, -1000);
        rightEye.setPosition(-1000, -1000);
        staff.setPosition(-1000, -1000);
        staffCross.setPosition(-1000, -1000);
    }
    else {
        lowerBody.setPosition(x, y + tileSize / 2);
        upperBody.setPosition(x, y);
        hat.setPoint(0, sf::Vector2f(x + tileSize / 2, y - tileSize / 2));
        hat.setPoint(1, sf::Vector2f(x - 10, y));
        hat.setPoint(2, sf::Vector2f(x + tileSize + 10, y));

        if (direction.y < 0) {
            leftEye.setPosition(-1000, -1000);
            rightEye.setPosition(-1000, -1000);
            staff.setPosition(x - tileSize * 0.5, y - tileSize - 23);
        }
        else if (direction.x < 0) {
            leftEye.setPosition(x + tileSize / 4, y + tileSize / 6);
            rightEye.setPosition(-1000, -1000);
            staff.setPosition(x - tileSize * 0.5, y - tileSize - 23);
        }
        else if (direction.x > 0) {
            leftEye.setPosition(-1000, -1000);
            rightEye.setPosition(x + 3 * tileSize / 4 - 11, y + tileSize / 6);
            staff.setPosition(x + tileSize * 1.1, y - tileSize - 23);
        }
        else {
            leftEye.setPosition(x + tileSize / 4, y + tileSize / 6);
            rightEye.setPosition(x + 3 * tileSize / 3 - 11, y + tileSize / 6);
            staff.setPosition(x + tileSize * 1.1, y - tileSize - 23);
        }

        staffCross.setPosition(
            staff.getPosition().x + staff.getSize().x / 2 - staffCross.getSize().x / 2,
            staff.getPosition().y + staff.getSize().y * (1.0 / 3.0)
        );
    }
}

void Witch::attack(sf::Vector2f target) {
    sf::Vector2f staffPos = staff.getPosition(); 
    sf::Vector2f crossPos(
        staffPos.x + staff.getSize().x / 2, 
        staffPos.y + staff.getSize().y * (1.0 / 3.0) 
    );

    projectiles.emplace_back(crossPos.x, crossPos.y, target.x, target.y, 5.f);
}



void Witch::update(sf::Vector2f archerPosition, Archer& archer, float deltaTime, const std::vector<std::vector<TileType>>& map, const std::vector<Tree>& trees) {
    if (isDead) {
        deathTimer += deltaTime;
        if (deathTimer >= 2.f) isVisible = false;
        return;
    }

    if (!archer.isAlive()) {
        projectiles.clear();  
        return;
    }

    // Таймер атаки
    attackCooldown -= deltaTime;

    // Таймер спавна мышей
    spawnCooldown -= deltaTime;
    if (spawnCooldown <= 0.f) {
        spawnBats();
        spawnCooldown = 50.0f; 
    }


    for (auto& bat : bats) {
        bat.update(archerPosition, archer, bats);
    }


    bats.erase(
        std::remove_if(bats.begin(), bats.end(), [](const Bat& b) { return b.getisdead(); }),
        bats.end()
    );


    sf::Vector2f witchPos(position.x * tileSize, position.y * tileSize);
    sf::Vector2f delta = archerPosition - witchPos;
    float radius = std::sqrt(delta.x * delta.x + delta.y * delta.y);


    if (radius <= 300.f && attackCooldown <= 0.f) {
        attack(archerPosition);
        attackCooldown = attackRate;
    }

    else if (radius > 300.f || radius < 150.f) {
        move(archerPosition, map, trees);
    }

  
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [&](WitchProjectile& projectile) {
                if (projectile.checkCollision(archer)) {
                    return true;  
                }
                projectile.update(archer, trees); 
                return !projectile.isActive(); 
            }),
        projectiles.end()
    );


    for (auto& projectile : projectiles) {
        projectile.update(archer, trees);
    }

    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [&](WitchProjectile& projectile) {
                return projectile.checkCollision(archer); 
            }),
        projectiles.end()
    );

    updateGraphics();
}


void Witch::spawnBats() {
    if (isDead) return; 

    sf::Vector2f spawnPos(position.x * tileSize, position.y * tileSize);

    bats.emplace_back(spawnPos.x - 30, spawnPos.y, 10, 20, 2.0f, 1.0f, 50.0f);  
    bats.emplace_back(spawnPos.x + 30, spawnPos.y, 10, 20, 2.0f, 1.0f, 50.0f); 
}

void Witch::move(sf::Vector2f target, const std::vector<std::vector<TileType>>& map, const std::vector<Tree>& trees) {
    sf::Vector2f witchPos(position.x * tileSize, position.y * tileSize);
    sf::Vector2f delta = target - witchPos;
    float radius = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float minDistance = 150.f;
    float maxDistance = 300.f;
    float baseStep = 5.f;

    if (radius < 1e-2) return; 

    sf::Vector2f newDirection = delta / radius; 
    sf::Vector2f nextPos = witchPos;

    if (radius > maxDistance) {
        nextPos += newDirection * baseStep;
    }
    else if (radius < minDistance) {
        nextPos -= newDirection * baseStep;
    }

    int newX = static_cast<int>(nextPos.x / tileSize);
    int newY = static_cast<int>(nextPos.y / tileSize);

    bool insideMap = newY >= 0 && newY < map.size() && newX >= 0 && newX < map[0].size();

    float movementModifier = 1.0f;
    if (insideMap && map[newY][newX] == TileType::Water) {
        movementModifier = 0.5f; 
    }

 
    sf::Vector2f adjustedPos = witchPos + (newDirection * baseStep * movementModifier);
    int adjustedX = static_cast<int>(adjustedPos.x);
    int adjustedY = static_cast<int>(adjustedPos.y);


    for (const Tree& tree : trees) {
        if (tree.isPathBlocked(adjustedX, adjustedY)) {
            if (adjustedX < tree.get_tree_x()) {
                // Идем вверх по Y
                adjustedY -= tileSize;  
            }
           
            else if (adjustedY > tree.get_tree_y()) {
                // Идем влево или вправо по X
                if (adjustedX < tree.get_tree_x()) {
                    adjustedX -= tileSize; 
                }
                else {
                    adjustedX += tileSize; 
                }
            }
            adjustedPos = sf::Vector2f(adjustedX, adjustedY);
            break;  
        }
    }

    position.x = adjustedPos.x / tileSize;
    position.y = adjustedPos.y / tileSize;
    direction = sf::Vector2i(std::round(newDirection.x), std::round(newDirection.y));

    updateGraphics();
}





void Witch::draw(sf::RenderWindow& window, const std::vector<Tree>& trees) {
    if (!isVisible) return;

    window.draw(upperBody);
    window.draw(lowerBody);
    window.draw(hat);

    if (!isDead) {
        window.draw(leftEye);
        window.draw(rightEye);
        window.draw(staff);
        window.draw(staffCross);
    }

    for (auto& projectile : projectiles) {
        projectile.draw(window);
    }

    for (auto& bat : bats) {
        bat.draw(window);
    }
}


void Witch::takeDamage(int damage) {
    if (isDead) return;

    health -= damage;
    if (health <= 0) {
        isDead = true;
        deathTimer = 0.f;
        projectiles.clear(); 
        updateGraphics();
    }
}

void Witch::setHealth(int a) {
    health = a;
}

bool Witch::isAlive() const {
    return !isDead;
}

int Witch::getX() const {
    return position.x;
}

int Witch::getY() const {
    return position.y;
}

int Witch::getWidth() const {
    return width;
}

int Witch::getHeight() const {
    return height;
}

int Witch::getHealth() const {
    return health;
}

bool Witch::is_Dead() const {
    return this->isDead;
}

bool Witch::is_Visible() const {
    return this->isVisible;
}