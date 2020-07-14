#ifndef TILESET_HPP
#define TILESET_HPP

#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class Tileset
{
public:
    Tileset(int texHandle, std::vector<sf::IntRect> rects);
    Tileset(int texHandle, sf::IntRect region, sf::Vector2f tileSize);

    virtual ~Tileset();

    const sf::IntRect &getTileCoords(const int tileId) const;

private:
    std::vector<sf::IntRect *> coords;
};

#endif