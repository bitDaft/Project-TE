/*
 * File: IDrawable.cpp
 * Project: Project-TE
 * Created Date: Sunday December 1st 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday December 1st 2019 8:34:11 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "DrawManager.hpp"
#include "IDrawable.hpp"
#include <assert.h>

DrawManager *IDrawable::_u = nullptr;

IDrawable::IDrawable(int pos) : canDraw(true)
{
  assert(pos > 0);
  _1 = pos - 1;
  _2 = _u->pushToQueue(pos, this);
}

IDrawable::~IDrawable()
{
  _u->removeFromQueue(_1, _2);
  _1 = -1;
  _2 = -1;
}

void IDrawable::initialize(DrawManager *uMan)
{
  if (!_u)
  {
    _u = uMan;
  }
}
void IDrawable::callDraw(const sf::Time &t,sf::RenderTexture &im)
{
  if (canDraw)
  {
    draw(t,im);
  }
}
void IDrawable::enableDraw()
{
  canDraw = true;
}
void IDrawable::disableDraw()
{
  canDraw = false;
}