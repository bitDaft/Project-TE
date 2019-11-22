/*
 * File: ResourceManager.cpp
 * Project: Project-TE
 * Created Date: Wednesday June 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday September 5th 2019 2:01:39 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "ResourceManager.hpp"

int ResourceManager::_id = 1;
std::unordered_map<int, ResourceManager::_texPtr> ResourceManager::_resourceMap;

ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
}

int ResourceManager::loadTexture(const char *path)
{
    _texPtr tex(new sf::Texture());
    if (tex->loadFromFile(path))
    {
        ResourceManager::_resourceMap.emplace(_id, std::move(tex));
        return _id++;
    }
    return 0;
}
sf::Texture &ResourceManager::getTexture(const int ID)
{
    return *ResourceManager::_resourceMap.at(ID);
}
void ResourceManager::unloadTexture(const int ID)
{
    ResourceManager::_resourceMap.erase(ID);
}