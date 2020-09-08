#include "TileMap.h"

TileMap::TileMap(int t, int map_w, int map_h, sf::Texture* texture) {
    t = t;
    map_w = map_w;
    map_h = map_h;
    texture = texture;
    generateVertices();// (x_o, y_o);
}

std::tuple<int, int> TileMap::getTextureCoordinates(int tile_index) {
    return std::make_tuple(1, 2);
}

int TileMap::getTileIndex(int coor_x, int coor_y) {
    if (coor_x < 0 || coor_y < 0 || coor_x >= t * map_w || coor_y >= t * map_h) {
        return -1;
    }
    //cout << "Coors: " << coor_x << "," << coor_y << endl;
    int x = floor(coor_x / t);
    int y = floor(coor_y / t);
    //cout << "Tile coors: " << x << "," << y << endl;
    return y * map_w + x;
}

void TileMap::setTileTexture(int coor_x, int coor_y, int texture_x, int texture_y) {
    int tile_index = getTileIndex(coor_x, coor_y);
    int v = tile_index * 4;
    //if tile hidden show
    if (vertices[v].color == sf::Color::Transparent) {
        for (int i = v; i < v + 4; i++) {
            vertices[i].color = sf::Color::White;
        }
    }
    vertices[v].texCoords = sf::Vector2f(texture_x, texture_y);
    vertices[v + 1].texCoords = sf::Vector2f(texture_x + t, texture_y);
    vertices[v + 2].texCoords = sf::Vector2f(texture_x + t, texture_y + t);
    vertices[v + 3].texCoords = sf::Vector2f(texture_x, texture_y + t);
}

bool TileMap::inTileMap(int coor_x, int coor_y) {
    if (coor_x >= 0 && coor_y >= 0 && coor_x < t * map_w && coor_y < t * map_h) {
        return true;
    }
    return false;
}


void TileMap::generateVertices() {
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(map_w * map_h * 4);
    int v = 0;
    for (unsigned int j = 0; j < map_h; ++j) {
        for (unsigned int i = 0; i < map_w; ++i) {
            vertices[v].position = sf::Vector2f(i * t, j * t);
            vertices[v + 1].position = sf::Vector2f(i * t + t, j * t);
            vertices[v + 2].position = sf::Vector2f(i * t + t, j * t + t);
            vertices[v + 3].position = sf::Vector2f(i * t, j * t + t);
            vertices[v].color = sf::Color::Transparent;
            vertices[v + 1].color = sf::Color::Transparent;
            vertices[v + 2].color = sf::Color::Transparent;
            vertices[v + 3].color = sf::Color::Transparent;
            v = v + 4;
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = texture;

    target.draw(vertices, states);
}
