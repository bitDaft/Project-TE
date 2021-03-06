/*
 * File: IDrawable.cpp
 * Project: Project-TE
 * Created Date: Sunday December 1st 2019
 * Author: bitDaft
 * -----
 * Last Modified: Saturday December 28th 2019 11:41:23 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include <assert.h>

#include "DrawManager.hpp"
#include "IDrawable.hpp"

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
  canDraw = false;
}

void IDrawable::initialize(DrawManager *drawManager)
{
  if (!_u)
  {
    _u = drawManager;
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