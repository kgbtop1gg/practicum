#ifndef TREE_HPP
#define TREE_HPP

#include <SFML/Graphics.hpp>

class Archer;
class Witch;

class Tree {
private:
    int x, y;
    sf::RectangleShape rectangle;
    static const int minHeal = 100;
    static const int maxHeal = 300;
    sf::Clock healCooldownClock;
    float healCooldown = 1.0f; 

public:
    Tree(int x, int y);

    void draw(sf::RenderWindow& window);
    void set_position(int a, int b, std::vector<Tree>& trees);
    bool isNearOtherTree(const std::vector<Tree>& trees) const;
    bool isArcherBehindTree(const Archer& archer);
    int get_tree_x() const;
    int get_tree_y() const;
    bool isPathBlocked(int archerX, int archerY) const;
    void healArcherIfNearby(Archer& archer);
};

#endif // TREE_HPP
