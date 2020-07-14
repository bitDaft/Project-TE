
#include <Tileset.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "ResourceManager.hpp"

// Tileset::Tileset(const int texHandle, const std::vector<sf::IntRect *> &tiles)
Tileset::Tileset(const std::vector<sf::IntRect *> &tiles)
{
    // TODO : firgure out whether we need the texture to limit the tiles dimensions
    // sf::Vector2u texSize = ResourceManager::getTexture(texHandle).getSize();
    for (auto &tile : tiles)
    {
        // if (tile->left < 0 || tile->top < 0 || tile->left + tile->width > texSize.x || tile->top + tile->height > texSize.y)
        // {
        //     coords.clear();
        //     return;
        // }
        tiles.push_back(new sf::IntRect(*tile));
    }
}

Tileset::Tileset(const int texHandle, sf::IntRect &region, const sf::Vector2i &tileSize)
{
    sf::Vector2u texSize = ResourceManager::getTexture(texHandle).getSize();

    if (region.left < 0)
        region.left = 0;
    if (region.top < 0)
        region.top = 0;
    if (region.width < 0 || (region.width + region.left) > texSize.x)
        region.width = texSize.x - region.left;
    if (region.height < 0 ||
        (region.height + region.top) > texSize.y)
        region.height = texSize.y - region.top;

    const int columns = region.width / tileSize.x;
    const int rows = region.height / tileSize.y;

    sf::Vector2i position;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            position.x = region.+ (tileSize.x * i);
            position.y = region.top + (tileSize.y * j);
            tiles.push_back(new sf::IntRect(position, tileSize));
        }
    }
}

Tileset::~Tileset()
{
    for (sf::IntRect *&item : tiles)
    {
        delete item;
    }
    tiles.clear();
}

const sf::IntRect &Tileset::getTileCoords(const int tileId) const
{
    return *(tiles.at(tileId));
}