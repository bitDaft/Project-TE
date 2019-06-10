#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>


/**
 * * we are going to have separate maps for texture and font resource
 * ? or should it be made to have single map with a simple resource interface 
 */
class ResourceManager
{
public:
private:
std::unordered_map<unsigned int,std::unique_ptr<sf::Texture>> _resourceMap;
std::unordered_map<unsigned int,std::unique_ptr<sf::Font>> _fontMap;
};