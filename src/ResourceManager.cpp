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
sf::Texture &ResourceManager::getTexture(const int handle)
{
    return *ResourceManager::_resourceMap.at(handle);
}
void ResourceManager::unloadTexture(const int handle)
{
    ResourceManager::_resourceMap.erase(handle);
}

Animation &ResourceManager::getAnimation(const int handle)
{
    return *ResourceManager::_animMap.at(handle);
}
bool ResourceManager::loadAnimation(const int handle, const int texHandle, const std::vector<sf::IntRect *> &frames)
{
    Animation *animation = new Animation();
    animation->setTexture(ResourceManager::getTexture(texHandle));
    for (auto &frame : frames)
    {
        animation->addFrame(new sf::IntRect(frame->left, frame->top, frame->width, frame->height));
    }
    const auto status = ResourceManager::_animMap.emplace(handle, animation);
    assert(status.second);
    return status.second;
}
void ResourceManager::unloadAnimation(const int handle)
{
    delete ResourceManager::_animMap.at(handle);
    ResourceManager::_animMap.erase(handle);
}
static Tileset &ResourceManager::getTileset(const int handle)
{
    return *ResourceManager::_tilesetMap.at(handle);
}
static bool ResourceManager::loadTileset(const int handle, const std::vector<sf::IntRect *> &tiles)
{
    const auto status = ResourceManager::_tilesetMap.emplace(handle, new Tileset(tiles));
    assert(status.second);
    return status.second;
}
static bool ResourceManager::loadTileset(const int handle, const int texHandle, sf::IntRect &region, const sf::Vector2i &tileSize)
{
    const auto status = ResourceManager::_tilesetMap.emplace(handle, new Tileset(texHandle, region, tileSize));
    assert(status.second);
    return status.second;
}
static void ResourceManager::unloadTileset(const int handle)
{
    delete ResourceManager::_tilesetMap(handle);
    ResourceManager::_tilesetMap.erase(handle);
}

ResourceLoader &ResourceManager::getLoader(const int handle)
{
    return *ResourceManager::_loaderMap.at(handle);
}
bool ResourceManager::loadLoader(const int handle, const char *path)
{
    ResourceLoader *newLdr = new ResourceLoader(path);
    const auto status = ResourceManager::_loaderMap.emplace(handle, newLdr);
    assert(status.second);
    return status.second;
}
void ResourceManager::unloadLoader(const int handle)
{
    delete ResourceManager::_loaderMap.at(handle);
    ResourceManager::_loaderMap.erase(handle);
}