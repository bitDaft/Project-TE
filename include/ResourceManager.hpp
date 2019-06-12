#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    sf::Texture &getTexture(const unsigned int ID) const;
    unsigned int loadTexture(const char *path);

private:
    // Using unordered map as it provides 'near' O(1) lookup
    std::unordered_map<unsigned int, std::unique_ptr<sf::Texture>> _resourceMap;
    static unsigned int id;
};