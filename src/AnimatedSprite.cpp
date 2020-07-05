/*
 * File: AnimatedSprite.cpp
 * Project: Project-TE
 * Created Date: Sunday December 8th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday, March 24th 2020 8:57:54 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "AnimatedSprite.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

AnimatedSprite::AnimatedSprite()
    : playing(true),
      looping(true),
      anim(nullptr),
      currentFrame(0),
      elapsedTime(sf::seconds(0.f)),
      perFrameTime(sf::seconds(0.f))
{
}
AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::update(const sf::Time &dt)
{
  if (playing && anim)
  {
    elapsedTime += dt;
    if (elapsedTime >= perFrameTime)
    {
      elapsedTime = elapsedTime - perFrameTime;
      if (currentFrame + 1 < anim->getFrameCount())
      {
        currentFrame++;
      }
      else if (looping)
      {
        currentFrame = 0;
      }
      else
      {
        playing = false;
      }
      setCurrentFrame(currentFrame);
      // need to add callback stuff here. for now ignoring as to get a basic setup of animation working
    }
  }
}

void AnimatedSprite::setCurrentFrame(int frame)
{
  if (anim)
  {
    currentFrame = frame;
    const sf::IntRect rect = anim->getFrame(currentFrame);

    _v[0].position = sf::Vector2f(0.f, 0.f);
    _v[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
    _v[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
    _v[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

    float left = static_cast<float>(rect.left);// + 0.0001f;
    float right = left + static_cast<float>(rect.width);
    float top = static_cast<float>(rect.top);
    float bottom = top + static_cast<float>(rect.height);

    _v[0].texCoords = sf::Vector2f(left, top);
    _v[1].texCoords = sf::Vector2f(left, bottom);
    _v[2].texCoords = sf::Vector2f(right, bottom);
    _v[3].texCoords = sf::Vector2f(right, top);
  }
}

void AnimatedSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  if (anim)
  {
    states.transform *= getTransform();
    states.texture = &anim->getTexture();
    target.draw(_v, 4, sf::PrimitiveType::Quads, states);
  }
}

const Animation &AnimatedSprite::getAnimation()
{
  return *anim;
}

void AnimatedSprite::setColor(const sf::Color &color)
{
  _v[0].color = color;
  _v[1].color = color;
  _v[2].color = color;
  _v[3].color = color;
}

void AnimatedSprite::setAnimation(const Animation &animation)
{
  if (anim != (&animation))
  {
    anim = &animation;
    setCurrentFrame(0);
  }
}

void AnimatedSprite::setAnimationTime(const sf::Time &totalTime)
{
  if (anim)
  {
    perFrameTime = totalTime / (sf::Int64)anim->getFrameCount();
  }
}

void AnimatedSprite::play()
{
  playing = true;
}
void AnimatedSprite::pause()
{
  playing = false;
}
void AnimatedSprite::stop()
{
  playing = false;
  setCurrentFrame(0);
}
void AnimatedSprite::setLooping(bool loop)
{
  looping = loop;
}

bool AnimatedSprite::isLooping() const
{
  return looping;
}
bool AnimatedSprite::isPlaying() const
{
  return playing;
}