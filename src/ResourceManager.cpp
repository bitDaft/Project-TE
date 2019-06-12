#include "ResourceManager.hpp"

unsigned int ResourceManager::id = 0;

ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
}

unsigned int ResourceManager::loadTexture(const char *path)
{
    std::unique_ptr<sf::Texture> tex;
    if(tex->loadFromFile(path))
    {
        _resourceMap.emplace(id++,tex);
    }
    
}
sf::Texture &ResourceManager::getTexture(const unsigned int ID) const
{
}