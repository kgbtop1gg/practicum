#include "Tree.h"
#include "Archer.h"
#include "Witch.h"
#include <random>
#include <ctime>

const int tileSize = 20; 
const int mapWidth = 1500; 
const int mapHeight = 1100; 


Tree::Tree(int x, int y) : x(x), y(y), rectangle(sf::Vector2f(tileSize, tileSize)) {}

void Tree::draw(sf::RenderWindow& window) {
    if ((get_tree_x() + 3 * tileSize > mapWidth) || (get_tree_x() - 2 * tileSize < 0) ||
        (get_tree_y() + tileSize > mapHeight) || (get_tree_y() - 4 * tileSize < 0)) {
        return;
    }
    else {
        // Ствол
        rectangle.setFillColor(sf::Color(139, 69, 19)); 
        rectangle.setPosition(x, y);
        window.draw(rectangle);

   
        rectangle.setFillColor(sf::Color(139, 69, 19));
        rectangle.setPosition(x, y - tileSize);
        window.draw(rectangle);

 
        int step = x - 2 * tileSize;
        int y_ = y - 2 * tileSize;
        for (int j = 0; j < 2; ++j) {
            for (int i = 0; i < 5; ++i) {
                rectangle.setFillColor(sf::Color(0, 100, 0)); 
                rectangle.setPosition(step + i * tileSize, y_);
                window.draw(rectangle);
            }
            y_ = y_ - tileSize;
        }

        step = x - tileSize;
        for (int i = 0; i < 3; ++i) {
            rectangle.setFillColor(sf::Color(0, 100, 0)); 
            rectangle.setPosition(step + i * tileSize, y_);
            window.draw(rectangle);
        }
    }
}

bool Tree::isNearOtherTree(const std::vector<Tree>& trees) const {
    for (const Tree& otherTree : trees) {
       
        if ((x - 2 * tileSize < otherTree.x + 3 * tileSize &&
            x + 3 * tileSize > otherTree.x - 2 * tileSize) &&
            (y - 4 * tileSize < otherTree.y + tileSize &&
                y + tileSize > otherTree.y - 4 * tileSize)) {
            return true; 
        }
    }
    return false;
}

void Tree::set_position(int a, int b, std::vector<Tree>& trees) {
    if (a < 2 * tileSize || a > mapWidth - 3 * tileSize ||
        b < 4 * tileSize || b > mapHeight - tileSize) return;

   
    x = a;
    y = b;

    if (isNearOtherTree(trees)) {
        return; 
    }
}




int Tree::get_tree_x() const {
    return x;
}

int Tree::get_tree_y() const {
    return y;
}

bool Tree::isArcherBehindTree(const Archer& archer) {
    int archerX = archer.getPosition().x * tileSize;
    int archerY = archer.getPosition().y * tileSize;

    int treeX = get_tree_x();
    int treeY = get_tree_y();

   
    bool withinX = (archerX >= treeX - 2 * tileSize) && (archerX < treeX + 3 * tileSize);
    bool behindY = (archerY > treeY); 

    return true;
}

bool Tree::isPathBlocked(int archerX, int archerY) const {
    
    int treeBottomX1 = x;                 
    int treeBottomX2 = x + tileSize;        
    int treeBottomY = y;                    


    if (archerX >= treeBottomX1 && archerX < treeBottomX2 && archerY == treeBottomY) {
        return true;
    }

    return false;
}


void Tree::healArcherIfNearby(Archer& archer) {
    int archerX = archer.getPosition().x * 20;
    int archerY = archer.getPosition().y * 20;

    int treeX = get_tree_x();
    int treeY = get_tree_y();


    bool isSameY = (archerY == treeY) || (archerY == treeY - tileSize);
    bool isNearX = (abs(archerX - treeX) <= 2 * tileSize);

    if (isSameY && isNearX) {
    
        if (healCooldownClock.getElapsedTime().asSeconds() >= healCooldown) {
             static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
             std::uniform_int_distribution<int> dist(minHeal, maxHeal);
             int healing = dist(rng);
             archer.heal(healing);
             healCooldownClock.restart();
        }
    }
}
