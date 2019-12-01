/*
 * File: IUpdatable.cpp
 * Project: Project-TE
 * Created Date: Monday November 18th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday December 1st 2019 12:25:49 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "UpdateManager.hpp"
#include "IUpdatable.hpp"
#include <iostream>
#include <assert.h>

UpdateManager *IUpdatable::_u = nullptr;

IUpdatable::IUpdatable(int pos)
{
  assert(pos > 0);
  _1 = pos - 1;
  _2 = _u->pushToQueue(pos, this);
}

IUpdatable::~IUpdatable()
{
  _u->removeFromQueue(_1, _2);
  _1 = -1;
  _2 = -1;
}

void IUpdatable::initialize(UpdateManager *uMan)
{
  if (!_u)
  {
    _u = uMan;
  }
}
void IUpdatable::callUpdate(const sf::Time &t)
{
  if (canUpdate)
  {
    update(t);
  }
}
void IUpdatable::enableUpdate()
{
  canUpdate = true;
}
void IUpdatable::disableUpdate()
{
  canUpdate = false;
}