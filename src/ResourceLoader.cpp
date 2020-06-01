
#include "ResourceLoader.hpp"
#include "ResourceManager.hpp"

#include "Animation.hpp"

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

ResourceLoader::ResourceLoader(const char *path)
{
  file.open(path);
}
ResourceLoader::~ResourceLoader()
{
  file.close();
}

void ResourceLoader::load()
{
  // read line by line
  // set  mode based on lines starting with colon
  // if mode is texture  read twice call resource manager to load the texture
  // if mode is animation read 3 values , then loop for the frames and call resource amanger to load

  std::string str;
  std::stringstream ss;
  int mode = 0;

  if (file.is_open())
  {
    while (getline(file, str))
    {
      // std::cout << str << " 333\n";
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
          std::cout << str1 << "\n";
          ss1.clear();
          ss1 << str1;
          ss1 >> f1 >> f2 >> f3 >> f4;
          testani->addFrame(new sf::IntRect(f1, f2, f3, f4));
        }
        ResourceManager::loadAnimation(handle, testani);
        break;
      }
      default:
        break;
      }
      ss.clear();
    }
  }
}
void ResourceLoader::unload()
{
}
