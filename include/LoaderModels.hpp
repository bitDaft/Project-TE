

#ifndef LOADER_MODELS
#define LOADER_MODELS

#include <vector>

#include <SFML/Graphics/Rect.hpp>


struct TextureModel
{
  int handle;
  char *path;
};
struct AnimationModel
{
  int handle;
  int texHandle;
  int frameCount;

  std::vector<const sf::IntRect *> frames;
};
struct LoaderModel
{
  int handle;
  char *path;
};

#endif