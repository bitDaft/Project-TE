

#ifndef LOADER_HPP
#define LOADER_HPP

#include <vector>

#include "LoaderModels.hpp"

class Loader
{
public:
  Loader();
  Loader(const char *);
  ~Loader();

  bool loadFromFile(const char *);
  bool saveToFile(const char *);

  bool addTexture(TextureModel *);
  bool addAnimation(AnimationModel *);
  bool addLoader(LoaderModel *);

  const std::vector<TextureModel *> &getTexture();
  const std::vector<AnimationModel *> &getAnimation();
  const std::vector<LoaderModel *> &getLoader();

  bool removeTexture(const int);
  bool removeAnimation(const int);
  bool removeLoader(const int);

  int flags;

private:
  void clearData();
  std::vector<TextureModel *> textures;
  std::vector<AnimationModel *> animations;
  std::vector<LoaderModel *> loaders;
};

#endif