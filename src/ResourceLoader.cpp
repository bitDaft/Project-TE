
#include "ResourceLoader.hpp"
#include "ResourceManager.hpp"

#include "Animation.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>

ResourceLoader::ResourceLoader(const char *path)
{
  std::ifstream file;
  file.open(path);

  std::string str;
  std::stringstream ss;
  int mode = 0;

  // use an assert here if the file cannot be opened ????
  // assert doesnt run during prod run time.
  // soo.......

  //we should proabably change this to be a binary kind of file so we dont have to do string parsing
  // so lets make an application to create these loader files after this is done.
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
        TextureModels texture;
        ss << str;
        int handle;
        std::string file_path;
        ss >> handle >> file_path;
        texture.handle = handle;
        texture.path = file_path;
        textures.push_back(texture);
        break;
      }
      case 2: //animation
      {

        AnimationModels animation;
        int handle;
        int texHandle;
        int frames;
        int f1, f2, f3, f4;
        ss << str;
        ss >> handle >> texHandle >> frames;
        animation.handle = handle;
        animation.texHandle = texHandle;
        animation.frameCount = frames;
        std::string str1;
        std::stringstream ss1;
        while (frames-- > 0)
        {
          getline(file, str1);
          ss1.clear();
          ss1 << str1;
          ss1 >> f1 >> f2 >> f3 >> f4;
          animation.frames.emplace_back(new sf::IntRect(f1, f2, f3, f4));
        }
        animations.push_back(animation);
        break;
      }
      case 3:
      {
        LoaderModels loader;
        ss << str;
        int handle;
        std::string file_path;
        ss >> handle >> file_path;
        loader.handle = handle;
        loader.path = file_path;
        loaders.push_back(loader);
        // ResourceLoader *ldr = new ResourceLoader(file_path.c_str());
        // ResourceManager::loadLoader(handle, ldr);
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
ResourceLoader::~ResourceLoader()
{
}

void ResourceLoader::load()
{
  for (auto texture : textures)
  {
    ResourceManager::loadTextureFromFile(texture.handle, texture.path.c_str());
  }
  for (auto animation : animations)
  {
    Animation *anim = new Animation();
    anim->setTexture(ResourceManager::getTexture(animation.texHandle));
    for (auto frame : animation.frames)
    {
      anim->addFrame(new sf::IntRect(*frame));
    }
    ResourceManager::loadAnimation(animation.handle, anim);
  }
  for (auto loader : loaders)
  {
    ResourceLoader *ldr = new ResourceLoader(loader.path.c_str());
    ResourceManager::loadLoader(loader.handle, ldr);
  }
}
void ResourceLoader::unload()
{
  for (auto texture : textures)
  {
    ResourceManager::unloadTexture(texture.handle);
  }
  for (auto animation : animations)
  {
    ResourceManager::unloadAnimation(animation.handle);
  }
  for (auto loader : loaders)
  {
    ResourceManager::unloadLoader(loader.handle);
  }
}
