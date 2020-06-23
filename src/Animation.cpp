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

    // with resource loader now. if an animation is unloaded then it needs to be loaded again. then the momery of the frames will be delted.
    // so to load it again the file will need to be parsed again.
    // so lets not destroy the frames here
    // and just let the resource laoder destroy the frames.
    // just simply clearing the frames array will be more than enough for here i guess
    // then what is the animation object is created manually then the intrects will leak
    // dammnn .. this cant just be simply resolved huh?
    // well it can be solved if the momeroy of the frames stored here and in the loader are different .. then clearing it here will be no problem.
    // i think we will do that and keep both the frames data separate and have ti cleared here.
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