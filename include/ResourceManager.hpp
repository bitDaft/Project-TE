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

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    static sf::Texture &getTexture(const int ID);
    static int loadTexture(const char *path);
    static void unloadTexture(const int ID);

private:
    typedef std::unique_ptr<sf::Texture> _texPtr;

    // ^Using unordered map as it provides 'near' O(1) lookup albeit memory hog
    static std::unordered_map<int, _texPtr> _resourceMap;
    static int _id;
};
#endif
