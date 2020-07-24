

#ifndef LOADER_MODEL_HPP
#define LOADER_MODEL_HPP

#include <vector>
#include <string>

#include <SFML/Graphics/Rect.hpp>

struct TextureModels
{
  int handle;
  std::string path;
};
struct AnimationModels
{
  int handle;
  int texHandle;
  int frameCount;

  std::vector<const sf::IntRect *> frames;
};
struct LoaderModels
{
  int handle;
  std::string path;
};

#endif