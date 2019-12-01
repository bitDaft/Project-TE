/*
 * File: IDrawable.hpp
 * Project: Project-TE
 * Created Date: Sunday December 1st 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday December 1st 2019 8:34:11 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
class DrawManager;

class IDrawable
{
public:
  IDrawable(int);
  virtual ~IDrawable();
  void callDraw(const sf::Time &,sf::RenderTexture &);
  static void initialize(DrawManager *);

protected:
  void enableDraw();
  void disableDraw();

private:
  virtual void draw(const sf::Time &,sf::RenderTexture &) = 0;

private:
  int _1;
  int _2;
  bool canDraw;
  static DrawManager *_u;
};

#endif