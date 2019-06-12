#include "ResourceManager.hpp"

unsigned int ResourceManager::id = 1;

ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
}

unsigned int ResourceManager::loadTexture(const char *path)
{
    texPtr tex(new sf::Texture());
    if (tex->loadFromFile(path))
    {
        _resourceMap.emplace(id, std::move(tex));
        return id++;
    }
    return 0;
}
sf::Texture &ResourceManager::getTexture(const unsigned int ID) const
{
    return *_resourceMap.at(ID);
}