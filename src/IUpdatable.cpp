/*
 * File: IUpdatable.cpp
 * Project: Project-TE
 * Created Date: Monday November 18th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday November 20th 2019 11:02:17 am
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
  _u->pushToQueue(pos, this);
}

IUpdatable::~IUpdatable()
{
  _u = nullptr;
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