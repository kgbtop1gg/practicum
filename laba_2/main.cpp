#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>

#include "Coin.h"
#include "Bomb.h"
#include "Bat.h"
#include "Arrow.h"
#include "Archer.h"
#include "Witch.h"
#include "Tree.h"
#include "TileType.h"



const int mapWidth = 1500;
const int mapHeight = 1000;
const int tileSize = 20;

sf::RenderWindow window(sf::VideoMode(1500, 600), "Window Size Example");

std::vector<std::vector<TileType>> generateMap(int width, int height, std::vector<Tree>& trees) {
    std::vector<std::vector<TileType>> map(height, std::vector<TileType>(width, Grass));
    std::srand(std::time(nullptr));

  
    for (int i = 0; i < 50; ++i) {
        int x = std::rand() % width;
        int y = std::rand() % height;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
                    map[y + dy][x + dx] = Water;
                }
            }
        }
    }


    for (int i = 0; i < 20; ++i) {
        int x, y;
        bool validPosition = false;

        for (int attempts = 0; attempts < 50; ++attempts) {
            x = std::rand() % width;
            y = std::rand() % height;

            Tree tree(x * tileSize, y * tileSize);

            if (map[y][x] == Grass && !tree.isNearOtherTree(trees)) {
                validPosition = true;
                break;
            }
        }

        if (validPosition) {
            trees.emplace_back(x * tileSize, y * tileSize);
        }
    }

    return map;
}


void spawnWave1(std::vector<Bat>& bats, int waveLevel, int tileSize, int mapWidth, int mapHeight) {
    int batCount = 5 + (waveLevel - 1) * 3; 
    int batHealth = 1000 + (waveLevel - 1) * 150;

    for (int i = 0; i < batCount; ++i) {
        float angle = i * (360.f / batCount);
        float x = mapWidth / 2 + (mapWidth / 3) * cos(angle * 3.14159f / 180.f);
        float y = mapHeight / 2 + (mapHeight / 3) * sin(angle * 3.14159f / 180.f);
        bats.emplace_back(x, y, 5, 7, 2, 1.5, 10);
        bats.back().set_health(batHealth);
    }
}

void spawnWave2(std::vector<Witch>& witches, int waveLevel, int tileSize, int mapWidth, int mapHeight) {
    int witchCount = 3 + (waveLevel - 1) * 2; 
    int witchHealth = 100 + (waveLevel - 1) * 30;

    for (int i = 0; i < witchCount; ++i) {
        int x = std::rand() % (mapWidth / tileSize) * tileSize;
        int y = std::rand() % (mapHeight / tileSize) * tileSize;
        witches.emplace_back(x, y, 80, 80, 0.08, 100);
        witches.back().setHealth(witchHealth);
    }
}

void spawnWave3(std::vector<Bat>& bats, std::vector<Witch>& witches, int waveLevel, int tileSize, int mapWidth, int mapHeight) {
    spawnWave1(bats, waveLevel, tileSize, mapWidth, mapHeight / 2); 
    spawnWave2(witches, waveLevel, tileSize, mapWidth, mapHeight);
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1400, 1050), "Archer vs enemies");
    sf::Clock clock;
    bool gameover = false;

    std::vector<Tree> trees;
    std::vector<Witch> witches;
    std::vector<Coin> coins;
    std::vector<Bat> bats;
    std::vector<Bomb> bombs;

    std::vector<std::vector<TileType>> map = generateMap(mapWidth / tileSize, mapHeight / tileSize, trees);
    Archer archer(5, 5, 0);
    
    for (int i = 0; i < 25; ++i) {
        bool placed = false;

        while (!placed) {
            int x = std::rand() % (mapWidth / tileSize);
            int y = std::rand() % (mapHeight / tileSize);

            if (map[y][x] == Grass) {
                bombs.emplace_back(x * tileSize, y * tileSize, tileSize);
                placed = true;
            }
        }
    }

    int waveLevel = 1;
    int currentSubWave = 1;

    spawnWave1(bats, waveLevel, tileSize, mapWidth, mapHeight);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) archer.move(0, -1, map, trees, coins);
                else if (event.key.code == sf::Keyboard::A) archer.move(-1, 0, map, trees, coins);
                else if (event.key.code == sf::Keyboard::S) archer.move(0, 1, map, trees, coins);
                else if (event.key.code == sf::Keyboard::D) archer.move(1, 0, map, trees, coins);
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                archer.attack(tileSize);
        }

        archer.update(window, bombs, bats, witches, trees, coins, gameover);

        for (auto& bomb : bombs) {
            bomb.update(tileSize);
        }

        float deltaTime = clock.restart().asSeconds();

        for (auto& witch : witches)
            witch.update(sf::Vector2f(archer.getPosition().x * tileSize, archer.getPosition().y * tileSize), archer, deltaTime, map, trees);

        for (auto& bat : bats)
            bat.update(sf::Vector2f(archer.getPosition().x * tileSize, archer.getPosition().y * tileSize), archer, bats);

        witches.erase(std::remove_if(witches.begin(), witches.end(),
            [](const Witch& w) { return !w.is_Visible(); }), witches.end());

        bats.erase(std::remove_if(bats.begin(), bats.end(),
            [](const Bat& b) { return b.getisdead(); }), bats.end());

        window.clear();

        for (int y = 0; y < map.size(); ++y) {
            for (int x = 0; x < map[y].size(); ++x) {
                sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
                tile.setPosition(x * tileSize, y * tileSize);
                tile.setFillColor(map[y][x] == Grass ? sf::Color(34, 139, 34) : sf::Color::Blue);
                window.draw(tile);
            }
        }

        archer.draw(trees, window);

        for (auto& bomb : bombs) {
            bomb.draw(window);
        }
       

        for (auto& witch : witches)
            witch.draw(window, trees);

        for (auto& bat : bats)
            bat.draw(window);

        for (auto& tree : trees) {
            tree.healArcherIfNearby(archer);
            tree.draw(window);
        }

        for (auto& coin : coins)
            coin.draw(window);

        window.display();

      
        if (bats.empty() && witches.empty()) {
            currentSubWave++;

            if (currentSubWave > 3) {
                currentSubWave = 1;
                waveLevel++;
            }

            if (currentSubWave == 1) {
                spawnWave1(bats, waveLevel, tileSize, mapWidth, mapHeight);
            }
            else if (currentSubWave == 2) {
                spawnWave2(witches, waveLevel, tileSize, mapWidth, mapHeight);
            }
            else if (currentSubWave == 3) {
                spawnWave3(bats, witches, waveLevel, tileSize, mapWidth, mapHeight);
            }
        }
    }

    return 0;
}
