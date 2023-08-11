#include "../include/Map.h"

Map::Map() {
    TileMap = new sf::String[HEIGHT_MAP] {
        "000000000000000000000000000000",
        "0022         1  1         2200",
        "0022         1  1         2200",
        "00  11  11  11  11  11  11  00",
        "00  112211  11  11  11  11  00",
        "00  11  11  11  11  11  11  00",
        "00  11  11  11  11  11  11  00",
        "00  112211  112211  11  11  00",
        "00  11  11  112211  11  11  00",
        "00  11  11  11  11  11  11  00",
        "00  11  11          11  11  00",
        "00  11  11          11  11  00",
        "00          11  11      11  00",
        "00          11  11      11  00",
        "0011111111          1111112200",
        "0022111111          1111111100",
        "00  11      11  11          00",
        "00  11      112211          00",
        "00  11  11  112211  11  11  00",
        "00  11  11  11  11  11  11  00",
        "00  11  11  11  11  112211  00",
        "00  11  11  11  11  11  11  00",
        "00  11  11          11  11  00",
        "00  11  11          112211  00",
        "00  11  11   1111   11  11  00",
        "0022         1  1         2200",
        "0022         1  1         2200",
        "000000000000000000000000000000",
    };

    TileMap2 = new sf::String[HEIGHT_MAP] {
        "000000000000000000000000000000",
        "0022         1  1         2200",
        "0022         1  1         2200",
        "0011  1111   1111   1111  1100",
        "00    1111          1111    00",
        "00    1111          1111    00",
        "00    1111          1111    00",
        "00    2222   2222   2222    00",
        "00    1111          1111    00",
        "00    1111          1111    00",
        "00    2222   2222   2222    00",
        "00    2222   2222   2222    00",
        "00                          00",
        "00                          00",
        "0022  22  22  22  22  22  2200",
        "0022  22  22  22  22  22  2200",
        "00                          00",
        "00                          00",
        "00    2222   2222   2222    00",
        "00    2222   2222   2222    00",
        "00    1111          1111    00",
        "00    1111          1111    00",
        "00    2222   2222   2222    00",
        "00                          00",
        "0022         1111         2200",
        "00           1  1           00",
        "00           1  1           00",
        "000000000000000000000000000000",
    };

    TileMap3 = new sf::String[HEIGHT_MAP] {
        "000000000000000000000000000000",
        "00           1  1           00",
        "00           1  1           00",
        "00           1111           00",
        "00                          00",
        "00                          00",
        "00                          00",
        "00   2222            2222   00",
        "00                          00",
        "00                          00",
        "00                          00",
        "00                          00",
        "00                          00",
        "0022      2222222222      2200",
        "0022      2222222222      2200",
        "00                          00",
        "00                          00",
        "00                          00",
        "00                          00",
        "00                          00",
        "00   2222            2222   00",
        "00                          00",
        "00                          00",
        "00                          00",
        "00           1111           00",
        "00           1  1           00",
        "00           1  1           00",
        "000000000000000000000000000000",
    };

    

    mTexture.loadFromFile("media/groundSprites.png");
    mTexture.setSmooth(true);
    mSprite.setTexture(mTexture);
}

void Map::break_wall(const int &i, const int &j) {
    TileMap[i][j] = ' ';
}

void Map::draw(sf::RenderWindow &window) {
    for (int i(0); i < HEIGHT_MAP; i++)
        for (int j(0); j < WIDTH_MAP; j++) {
            switch (TileMap[i][j]) {
                case ' ':
                    mSprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
                    break;

                case '0':
                    mSprite.setTextureRect(sf::IntRect(72, 0, 24, 24));
                    break;

                case '1':
                    mSprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
                    break;

                case '2':
                    mSprite.setTextureRect(sf::IntRect(48, 0, 24, 24));
                    break;
            }

            mSprite.setPosition(j * 24, i * 24);
            window.draw(mSprite);
        }
}

std::vector<std::vector<Node>> Map::createGrid(int nRows, int nCols) {
    std::vector<std::vector<Node>> grid(nRows, std::vector<Node>(nCols));

    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            grid[i][j].x = i;
            grid[i][j].y = j;
            grid[i][j].g = 0;
            grid[i][j].h = 0;
            grid[i][j].f = grid[i][j].g + grid[i][j].h;
            grid[i][j].bIsBrick = false;
            grid[i][j].bIsSteel = false;
            grid[i][j].parent = nullptr;
        }
    }

    return grid;
}

bool Map::isWithinBounds(int x, int y, int rows, int columns) {      // Checks if the node is still within bounds of the grid
	return (x >= 0 && x < rows && y >= 0 && y < columns);
}