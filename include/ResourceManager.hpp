/*
 * File: ResourceManager.hpp
 * Project: Project-TE
 * Created Date: Wednesday June 12th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 1:45:52 am
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

    sf::Texture &getTexture(const unsigned int ID) const;
    unsigned int loadTexture(const char *path);

private:
    typedef std::unique_ptr<sf::Texture> _texPtr;

    // ^Using unordered map as it provides 'near' O(1) lookup albeit memory hog
    std::unordered_map<unsigned int, _texPtr> _resourceMap;
    static unsigned int _id;
};
#endif
