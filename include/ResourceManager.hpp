/*
 * File: ResourceManager.hpp
 * Project: Project-TE
 * Created Date: Wednesday June 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday September 5th 2019 2:01:39 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

#include "Animation.hpp"
#include "ResourceLoader.hpp"
#include "Tileset.hpp"

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    static void init();

    static sf::Texture &getTexture(const int);
    static bool loadTextureFromFile(const int, const char *);
    static bool loadTexture(const int, const sf::Texture *);
    static void unloadTexture(const int);

    static Animation &getAnimation(const int);
    static bool loadAnimation(const int, const int, const std::vector<sf::IntRect *> &);
    static bool loadAnimation(const int, const int, const int, const std::vector<int> &);
    static void unloadAnimation(const int);

    static Tileset &getTileset(const int);
    static bool loadTileset(const int, const std::vector<sf::IntRect *> &);
    static bool loadTileset(const int, const int, sf::IntRect &, const sf::Vector2i &);
    static void unloadTileset(const int);

    static ResourceLoader &getLoader(const int);
    static bool loadLoader(const int, const char *path);
    static void unloadLoader(const int);

private:
    typedef std::unique_ptr<sf::Texture> _texPtr;
    // typedef std::unique_ptr<Animation> _animPtr;

    // ^Using unordered map as it provides 'near' O(1) lookup albeit memory hog
    static std::unordered_map<int, _texPtr> _resourceMap;
    static std::unordered_map<int, Tileset *> _tilesetMap;
    static std::unordered_map<int, Animation *> _animMap;
    static std::unordered_map<int, ResourceLoader *> _loaderMap;
};
#endif
