/*
 * File: IUpdatable.cpp
 * Project: Project-TE
 * Created Date: Monday November 18th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday November 21st 2019 10:43:54 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "UpdateManager.hpp"
#include "IUpdatable.hpp"
#include <iostream>

UpdateManager *IUpdatable::_u = nullptr;

IUpdatable::IUpdatable(int pos)
{
  _1 = pos;
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
    std::cout << "Initializing";
    _u = uMan;
  }
}
void IUpdatable::callUpdate(const sf::Time &t)
{
  update(t);
}