/*
 * File: AnimatedSprite.hpp
 * Project: Project-TE
 * Created Date: Sunday December 8th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:41:38 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Animation.hpp"

/** 
 * this class replaces the default sprite object to show an animation
 * TODO: need to implement functions used in sprite
 * TODO: Change from quads to triangles 
*/
class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
  // contructor and destructor
  AnimatedSprite();
  virtual ~AnimatedSprite();

  /**
   * Sets the animation to be shown for this sprite  
   * @param animation the animation to be used
   * @return void
   */
  void setAnimation(const Animation &animation);

  /**
   * Sets the amount of time needed to show the complete animation  
   * @param totalTime the total time needed for the animation
   * @return void
   */
  void setAnimationTime(const sf::Time &totalTime);

  /**
   * Sets the current frame  
   * @param frame the new frame position
   * @return void
   */
  void setCurrentFrame(int frame);

  /**
   * Gets the current Animation object reference  
   * @return const Animation & the reference to the currently held animation
   */
  const Animation &getAnimation();

  /**
   * allow playing of the animation  
   * @return void
   */
  void play();

  /**
   * pause the playing of the current animation  
   * @return void
   */
  void pause();

  /**
   * stop the animation and reset to first frame  
   * @return void
   */
  void stop();

  /**
   * Set whether the animation can loop or not  
   * @param loop whether to loop or not
   * @return void
   */
  void setLooping(bool loop);

  /**
   * Update the animation based on elapsed time  
   * @param dt the elapsed time
   * @return void
   */
  void update(const sf::Time &dt);

  /**
   * Check whether the animation is looping or not  
   * @return bool whether it is looping
   */
  bool isLooping() const;

  /**
   * Whether the animation is playing or stopped  
   * @return bool whether it is playing
   */
  bool isPlaying() const;

  /**
   * Set the color of the vertices  
   * @param color the color of the vertices to be set
   * @return void
   */
  void setColor(const sf::Color &color);

  // TODO: need to implement
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