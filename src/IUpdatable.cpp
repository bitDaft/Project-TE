/*
 * File: IUpdatable.cpp
 * Project: Project-TE
 * Created Date: Monday November 18th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Saturday, March 28th 2020 6:47:41 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "UpdateManager.hpp"
#include "IUpdatable.hpp"
#include <iostream>
#include <assert.h>

UpdateManager *IUpdatable::_u = nullptr;

IUpdatable::IUpdatable(int pos) : canUpdate(true)
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

void IUpdatable::initialize(UpdateManager *updateManager)
{
  if (!_u)
  {
    _u = updateManager;
  }
}

void IUpdatable::disabledUpdate(const sf::Time &)
{
  
}
void IUpdatable::enableUpdate()
{
  canUpdate = true;
}
void IUpdatable::disableUpdate()
{
  canUpdate = false;
}