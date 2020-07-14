

#ifndef LOADER_MODELS_HPP
#define LOADER_MODELS_HPP

#include <vector>
#include <string>

#include <SFML/Graphics/Rect.hpp>

struct TextureModel
{
  int handle;
  std::string path;
};
struct AnimationModel
{
  int handle;
  int texHandle;
  std::vector<sf::IntRect *> frames;
};
struct LoaderModel
{
  int handle;
  std::string path;
};
struct TilesetModel
{
  int handle;
  int texHandle;
  bool regionBased;
  sf::IntRect region;
  sf::Vector2i tileSize;
  std::vector<sf::IntRect *> tiles;
};

#endif