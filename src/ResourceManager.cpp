/*
 * File: ResourceManager.cpp
 * Project: Project-TE
 * Created Date: Wednesday June 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday June 28th 2019 12:04:47 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "ResourceManager.hpp"

unsigned int ResourceManager::_id = 1;

ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
}

unsigned int ResourceManager::loadTexture(const char *path)
{
    _texPtr tex(new sf::Texture());
    if (tex->loadFromFile(path))
    {
        _resourceMap.emplace(_id, std::move(tex));
        return _id++;
    }
    return 0;
}
sf::Texture &ResourceManager::getTexture(const unsigned int ID) const
{
    return *_resourceMap.at(ID);
}