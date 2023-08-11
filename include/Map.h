#pragma once
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Enemy.h"

enum MapNum {
    Map1, Map2, Map3
};

struct Node {
    int x, y;
    int f, g, h;
    Node* parent;

    bool bIsBrick;
    bool bIsSteel;

    bool operator<(const Node& other) const {
        return g + h > other.g + other.h;
    }
};

class Map : private sf::NonCopyable {
private:
    static const int HEIGHT_MAP = 28;
    static const int WIDTH_MAP = 30;

    sf::String *actualMap;
    sf::Texture mTexture;
    sf::Sprite mSprite;

public:
    sf::String *TileMap, *TileMap2, *TileMap3;

public:
    Map();

    void break_wall(const int &i, const int &j);
    const char get_tile(const int &i, const int &j) { return TileMap[i][j]; }
    void draw(sf::RenderWindow &window);
    std::vector<std::vector<Node>> createGrid(int nRows, int nCols); 
    bool isWithinBounds(int x, int y, int rows, int columns);
};
