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
#include <cassert>

std::unordered_map<int, ResourceManager::_texPtr> ResourceManager::_resourceMap;
std::unordered_map<int, Animation *> ResourceManager::_animMap;
std::unordered_map<int, ResourceLoader *> ResourceManager::_loaderMap;

ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
}

void ResourceManager::init()
{
    ResourceManager::_resourceMap.reserve(30);
    ResourceManager::_animMap.reserve(30);
    ResourceManager::_loaderMap.reserve(30);
}

bool ResourceManager::loadTextureFromFile(const int handle, const char *path)
{
    _texPtr tex(new sf::Texture());
    if (tex->loadFromFile(path))
    {
        const auto status = ResourceManager::_resourceMap.emplace(handle, std::move(tex));
        assert(status.second);
        return status.second;
    }
    return false;
}
bool ResourceManager::loadTexture(const int handle, const sf::Texture *texture)
{
    _texPtr tex(new sf::Texture(*texture));
    const auto status = ResourceManager::_resourceMap.emplace(handle, std::move(tex));
    assert(status.second);
    return status.second;
}
sf::Texture &ResourceManager::getTexture(const int ID)
{
    return *ResourceManager::_resourceMap.at(ID);
}
void ResourceManager::unloadTexture(const int ID)
{
    ResourceManager::_resourceMap.erase(ID);
}

Animation &ResourceManager::getAnimation(const int ID)
{
    return *ResourceManager::_animMap.at(ID);
}
bool ResourceManager::loadAnimation(const int handle, Animation *anim)
{
    const auto status = ResourceManager::_animMap.emplace(handle, anim);
    assert(status.second);
    return status.second;
}
void ResourceManager::unloadAnimation(const int ID)
{
    delete ResourceManager::_animMap.at(ID);
    ResourceManager::_animMap.erase(ID);
}

ResourceLoader &ResourceManager::getLoader(const int ID)
{
    return *ResourceManager::_loaderMap.at(ID);
}
bool ResourceManager::loadLoader(const int handle, ResourceLoader *ldr)
{
    const auto status = ResourceManager::_loaderMap.emplace(handle, ldr);
    assert(status.second);
    return status.second;
}
void ResourceManager::unloadLoader(const int ID)
{
    delete ResourceManager::_loaderMap.at(ID);
    ResourceManager::_loaderMap.erase(ID);
}