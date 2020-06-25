

#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP

#include <vector>

#include "LoaderModels.hpp"

class ResourceLoader
{
public:
  ResourceLoader(const char *);
  virtual ~ResourceLoader();

  void load();
  void unload();

private:
  std::vector<TextureModels> textures;
  std::vector<AnimationModels> animations;
  std::vector<LoaderModels> loaders;
};

#endif