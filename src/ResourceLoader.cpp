
#include "ResourceLoader.hpp"
#include "ResourceManager.hpp"

#include "Animation.hpp"

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

ResourceLoader::ResourceLoader(const char *path)
    : file_path(path)
{
}
ResourceLoader::~ResourceLoader()
{
}

void ResourceLoader::load()
{
  file.open(file_path);
  std::string str;
  std::stringstream ss;
  int mode = 0;

  if (file.is_open())
  {
    while (getline(file, str))
    {
      if (str[0] == ':')
      {
        if (!str.compare(":TEXTURE"))
        {
          mode = 1;
        }
        else if (!str.compare(":ANIM"))
        {
          mode = 2;
        }
        else if (!str.compare(":LOADER"))
        {
          mode = 3;
        }
        continue;
      }
      else if (!str.length())
      {
        continue;
      }
      switch (mode)
      {
      case 1: //texture
      {
        ss << str;
        int handle;
        std::string pp;
        ss >> handle >> pp;
        ResourceManager::loadTextureFromFile(handle, pp.c_str());
        break;
      }
      case 2: //animation
      {
        int handle;
        int texHandle;
        int frames;

        int f1, f2, f3, f4;
        ss << str;
        ss >> handle >> texHandle >> frames;
        std::string str1;
        std::stringstream ss1;
        Animation *testani = new Animation();
        testani->setTexture(ResourceManager::getTexture(texHandle));
        while (frames-- > 0)
        {
          getline(file, str1);
          ss1.clear();
          ss1 << str1;
          ss1 >> f1 >> f2 >> f3 >> f4;
          testani->addFrame(new sf::IntRect(f1, f2, f3, f4));
        }
        ResourceManager::loadAnimation(handle, testani);
        break;
      }
      case 3:
      {
        ss << str;
        int handle;
        std::string pp;
        ss >> handle >> pp;
        ResourceLoader *ldr = new ResourceLoader(pp.c_str());
        ResourceManager::loadLoader(handle, ldr);
        break;
      }
      default:
        break;
      }
      ss.clear();
    }
  }
  file.close();
}
void ResourceLoader::unload()
{
}
