/*
 * File: IUpdatable.cpp
 * Project: Project-TE
 * Created Date: Monday November 18th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday November 22nd 2019 9:04:30 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "DrawManager.hpp"
#include "IDrawable.hpp"
#include <iostream>
#include <assert.h>

DrawManager *IDrawable::_u = nullptr;

IDrawable::IDrawable(int pos)
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
void IDrawable::callDraw(const sf::Time &t)
{
  draw(t);
}