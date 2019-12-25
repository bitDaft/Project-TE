/*
 * File: Animation.cpp
 * Project: Project-TE
 * Created Date: Sunday December 8th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday December 8th 2019 10:34:36 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "Animation.hpp"

Animation::Animation(const int &&reserve)
    : refTex(nullptr),
      _c(true)
{
  frames.reserve(reserve);
}
Animation::~Animation()
{
  if (_c)
  {
    // TODO:looping remove the rects .. let it leak for now
    // ^let OS clean up for now on close
  }
  frames.clear();
}

void Animation::addFrame(const sf::IntRect *rect, int count)
{
  for (int i = 0; i < count; i++)
  {
    frames.emplace_back(rect);
  }
}
int Animation::getFrameCount() const
{
  return frames.size();
}
void Animation::setTexture(const sf::Texture &texture)
{
  refTex = &texture;
}
const sf::IntRect &Animation::getFrame(int pos) const
{
  return *frames.at(pos);
}
const sf::Texture &Animation::getTexture() const
{
  return *refTex;
}
void Animation::preventRelease()
{
  _c = false;
}