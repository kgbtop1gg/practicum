#include "Arrow.h"
#include "Tree.h" 

#include <cmath>

const int TILE_SIZE = 30;

Arrow::Arrow(int startX, int startY, sf::Vector2f dir, int tileSize, int dmg, int spd)
    : direction(dir), maxDistance(10 * tileSize), damage(dmg), speed(spd) {

    position = sf::Vector2f(startX, startY);
    startPosition = position;

    // Форма стрелы
    arrowShape.setPointCount(7);
    arrowShape.setPoint(0, sf::Vector2f(0, -tileSize / 4.f));
    arrowShape.setPoint(1, sf::Vector2f(tileSize / 2.f, 0));
    arrowShape.setPoint(2, sf::Vector2f(0, tileSize / 4.f));
    arrowShape.setPoint(3, sf::Vector2f(0, tileSize / 8.f));
    arrowShape.setPoint(4, sf::Vector2f(-tileSize / 2.f, tileSize / 8.f));
    arrowShape.setPoint(5, sf::Vector2f(-tileSize / 2.f, -tileSize / 8.f));
    arrowShape.setPoint(6, sf::Vector2f(0, -tileSize / 8.f));

    arrowShape.setFillColor(sf::Color::Red);
    arrowShape.setOrigin(sf::Vector2f(tileSize / 4.f, 0));
    arrowShape.setPosition(position);

    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;
    arrowShape.setRotation(angle);
}

void Arrow::move() {
    position += direction * static_cast<float>(speed);
    arrowShape.setPosition(position);
}

bool Arrow::hasReachedMaxDistance() const {
    float distanceTravelled = std::sqrt(
        std::pow(position.x - startPosition.x, 2) +
        std::pow(position.y - startPosition.y, 2)
    );
    return distanceTravelled >= static_cast<float>(maxDistance*2);
}

void Arrow::draw(sf::RenderWindow& window) {

    window.draw(arrowShape);
}

int Arrow::getDamage() const {
    return damage;
}

float Arrow::getX() const {
    return position.x;
}

float Arrow::getY() const {
    return position.y;
}

bool Arrow::checkCollisionWithTree(const Tree& tree) const {
    sf::FloatRect arrowBounds = arrowShape.getGlobalBounds();
    sf::FloatRect treeBase(
        static_cast<float>(tree.get_tree_x()),
        static_cast<float>(tree.get_tree_y()),
        static_cast<float>(TILE_SIZE),
        static_cast<float>(TILE_SIZE)
    );

    return arrowBounds.intersects(treeBase);
}
