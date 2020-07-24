
#include "ResourceLoader.hpp"
#include "ResourceManager.hpp"

#include "Animation.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>

ResourceLoader::ResourceLoader()
    : ldr(new Loader())
{
}
ResourceLoader::ResourceLoader(const char *path)
    : ldr(new Loader())
{
  loadFile(path);
}
ResourceLoader::~ResourceLoader()
{
  delete ldr;
}

bool ResourceLoader::loadFile(const char *path)
{
  ldr->loadFromFile(path);
  return !(ldr->flags < 0);
}

void ResourceLoader::load()
{
  for (auto &texture : ldr->getTexture())
  {
    ResourceManager::loadTextureFromFile(texture->handle, texture->path.c_str());
  }
  for (auto &tileset : ldr->getTileset())
  {
    if (tileset->regionBased)
    {
      ResourceManager::loadTileset(tileset->handle, tileset->texHandle, tileset->region, tileset->tileSize);
    }
    else
    {
      ResourceManager::loadTileset(tileset->handle, tileset->tiles);
    }
  }
  for (auto &animation : ldr->getAnimation())
  {
    if (animation->tileBased)
    {
      // TODO : loop through the tilemap and find the rects for it
      // TODO : add tileid to animation struct
      // std::vector<sf::IntRect *> tiles;
      // Tileset ts = ResourceManager::getTileset(animation->tileid); // !this field does not exist as of now in AnimationModel nor is it saved to ldr file.
      // for (auto &i : animation->tileids)
      // {
      //   const sf::IntRect &tile = ts.getTileCoords(i);
      //   tiles.push_back(new sf::IntRect(tile.left, tile.top, tile.width, tile.height));
      // }
      // ResourceManager::loadAnimation(animation->handle, animation->texHandle, tiles);
    }
    else
    {
      ResourceManager::loadAnimation(animation->handle, animation->texHandle, animation->frames);
    }
  }
  for (auto &loader : ldr->getLoader())
  {
    ResourceManager::loadLoader(loader->handle, loader->path.c_str());
  }
}
void ResourceLoader::unload()
{
  for (auto &texture : ldr->getTexture())
  {
    ResourceManager::unloadTexture(texture->handle);
  }
  for (auto &animation : ldr->getAnimation())
  {
    ResourceManager::unloadAnimation(animation->handle);
  }
  for (auto &loader : ldr->getLoader())
  {
    ResourceManager::unloadLoader(loader->handle);
  }
}
