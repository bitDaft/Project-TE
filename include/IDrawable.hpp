/*
 * File: IUpdatable.hpp
 * Project: Project-TE
 * Created Date: Monday November 18th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday November 21st 2019 10:43:54 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

#include <SFML/System/Time.hpp>
class DrawManager;

class IDrawable
{
public:
  IDrawable(int);
  virtual ~IDrawable();
  void callDraw(const sf::Time &);
  static void initialize(DrawManager *);

protected:
private:
  virtual void draw(const sf::Time &) = 0;

private:
  int _1;
  int _2;
  static DrawManager *_u;
};

#endif