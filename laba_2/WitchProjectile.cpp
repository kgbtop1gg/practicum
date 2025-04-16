#include "WitchProjectile.h"
#include <cmath>
#include "Archer.h"

const int tileSize = 60;

WitchProjectile::WitchProjectile(float startX, float startY, float targetX, float targetY, float speed)
    : x(startX), y(startY), radius(10.f), speed(speed), active(true) {
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(x, y);

    sf::Vector2f direction(targetX - x, targetY - y);
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = length != 0 ? direction / length * speed : sf::Vector2f(0, 0);
}

void WitchProjectile::update(Archer& archer, const std::vector<Tree>& trees) {
    if (!active) return;

    x += velocity.x;
    y += velocity.y;
    shape.setPosition(x, y);

    
    if (x < 0 || x > 1400 || y < 0 || y > 1050) {
        active = false;
        return;
    }

    
    sf::FloatRect projectileBounds(x, y, radius * 2, radius * 2);

    
    for (const Tree& tree : trees) {
        int trunkX = tree.get_tree_x();
        int trunkY = tree.get_tree_y();

        int tile = 20;  

     
        sf::FloatRect trunkBottom(trunkX, trunkY, tile, tile);
        sf::FloatRect trunkTop(trunkX, trunkY - tile, tile, tile);

        if (projectileBounds.intersects(trunkBottom) || projectileBounds.intersects(trunkTop)) {
            active = false;
            return;
        }
    }
}

void WitchProjectile::draw(sf::RenderWindow& window) {
    if (active) window.draw(shape);
}

bool WitchProjectile::checkCollision(Archer& archer) {
    
    float archerCenterX = archer.getPosition().x * 20 + 10;
    float archerCenterY = archer.getPosition().y * 20 - 10;

   
    float projectileCenterX = x + radius;
    float projectileCenterY = y + radius;

  
    float dx = projectileCenterX - archerCenterX;
    float dy = projectileCenterY - archerCenterY;
    float distance = std::sqrt(dx * dx + dy * dy);

 
    float combinedRadius = radius + 10;  

    if (distance <= combinedRadius) {
        archer.takeDamage(10); 
        active = false;       
        return true;
    }
    return false;
}




float WitchProjectile::getX() const { return x; }
float WitchProjectile::getY() const { return y; }
float WitchProjectile::getRadius() const { return radius; }


void WitchProjectile::setX(float newX) { x = newX; shape.setPosition(x, y); }
void WitchProjectile::setY(float newY) { y = newY; shape.setPosition(x, y); }
void WitchProjectile::setRadius(float newRadius) { radius = newRadius; shape.setRadius(radius); }
