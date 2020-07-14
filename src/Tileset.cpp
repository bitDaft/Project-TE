
#include <Tileset.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "ResourceManager.hpp"

Tileset::Tileset(int texHandle, std::vector<sf::IntRect> rects)
{
    for (sf::IntRect &rect : rects)
    {
        coords.push_back(new sf::IntRect(rect));
    }
}

Tileset::Tileset(int texHandle, sf::IntRect region, sf::Vector2i tileSize)
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
            coords.push_back(new sf::IntRect(position, tileSize));
        }
    }
}

Tileset::~Tileset()
{
    for (sf::IntRect *item : coords)
    {
        delete item;
    }
    coords.clear();
}

const sf::IntRect &Tileset::getTileCoords(const int tileId) const
{
    return *(coords.at(tileId));
}