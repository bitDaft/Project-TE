#ifndef TILESET_HPP
#define TILESET_HPP

#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class Tileset
{
public:
    // TODO : check why making this const is an error -fpermissive
    Tileset(const std::vector<sf::IntRect *> &tiles);
    Tileset(const int texHandle, sf::IntRect &region, const sf::Vector2i &tileSize);

    virtual ~Tileset();

    const sf::IntRect &getTileCoords(const int tileId) const;

private:
    std::vector<sf::IntRect *> tiles;
};

#endif