
#include <Tileset.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "ResourceManager.hpp"

Tileset::Tileset(const std::vector<sf::IntRect *> &newTiles)
{
    // TODO : firgure out whether we need the texture to limit the tiles dimensions
    // sf::Vector2u texSize = ResourceManager::getTexture(texHandle).getSize();
    for (auto &tile : newTiles)
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
    // ? Should the regions be bound by the texture.
    // ? or should we just accept that as the region
    // ^ since tilesets are basically useless on their own and their only purpose is to get the intrect
    // ^ which will then be used as texture coordinates
    // ^ but while the actual drawing we can just use any old texture as needed by passing that in
    // ^ so i wonder whether tying it down to textures has any merit and why not just let it be its own regions?
    // *for now we will leave it as it is and see if it actually works or not
    sf::Vector2u texSize = ResourceManager::getTexture(texHandle).getSize();

    if (region.left < 0)
        region.left = 0;
    if (region.top < 0)
        region.top = 0;
    if (region.width < 0 || (region.width + region.left) > static_cast<int>(texSize.x))
        region.width = texSize.x - region.left;
    if (region.height < 0 ||
        (region.height + region.top) > static_cast<int>(texSize.y))
        region.height = texSize.y - region.top;

    const int columns = region.width / tileSize.x;
    const int rows = region.height / tileSize.y;

    sf::Vector2i position;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            position.x = region.left + (tileSize.x * j);
            position.y = region.top + (tileSize.y * i);
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