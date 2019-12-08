/*
 * File: Animation.hpp
 * Project: Project-TE
 * Created Date: Sunday December 8th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday December 8th 2019 10:34:11 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

class Animation
{
public:
  Animation(const int && = 10);
  virtual ~Animation();

  void addFrame(const sf::IntRect *, int = 1);
  void setTexture(const sf::Texture &);
  int getFrameCount() const;
  const sf::IntRect &getFrame(int) const;
  const sf::Texture &getTexture() const;
  void preventRelease();

private:
  const sf::Texture *refTex;
  std::vector<const sf::IntRect *> frames;
  bool _c;
};

#endif