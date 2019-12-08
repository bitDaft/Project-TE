/*
 * File: AnimatedSprite.hpp
 * Project: Project-TE
 * Created Date: Sunday December 8th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday December 8th 2019 10:17:52 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <vector>

#include "Animation.hpp"

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
  AnimatedSprite();
  virtual ~AnimatedSprite();

  void setAnimation(const Animation &);
  void setAnimationTime(const sf::Time &);
  void setCurrentFrame(int);

  const Animation &getAnimation();

  void play();
  void pause();
  void stop();
  void setLooping(bool);

  void update(const sf::Time &);

  bool isLooping() const;
  bool isPlaying() const;

  void setColor(const sf::Color &);
  // sf::FloatRect getLocalBounds() const;
  // sf::FloatRect getGlobalBounds() const;

private:
  bool playing;
  bool looping;

  const Animation *anim;

  int currentFrame;
  sf::Time elapsedTime;
  sf::Time perFrameTime;

  sf::Vertex _v[4];

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif