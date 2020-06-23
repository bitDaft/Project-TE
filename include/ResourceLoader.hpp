

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
  std::vector<TextureModel> textures;
  std::vector<AnimationModel> animations;
  std::vector<LoaderModel> loaders;
};

#endif