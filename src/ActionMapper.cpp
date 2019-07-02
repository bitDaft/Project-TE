/*
 * File: ActionMapper.cpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday June 28th 2019 1:45:05 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "ActionMapper.hpp"

ActionMapper::ActionMapper() {}
ActionMapper::~ActionMapper() {}

void ActionMapper::bindInputToAction(sf::Keyboard::Key key, unsigned int action)
{
  _actionMapKeyboard[key] = action;
}

void ActionMapper::bindInputToAction(sf::Mouse::Button button, unsigned int action)
{
  _actionMapMouse[button] = action;
}

unsigned int ActionMapper::getBoundAction(sf::Keyboard::Key key)
{
  std::map<sf::Keyboard::Key, unsigned int>::iterator iter = _actionMapKeyboard.find(key);
  if (iter != _actionMapKeyboard.end())
  {
    return iter->second;
  }
  return 0;
}

unsigned int ActionMapper::getBoundAction(sf::Mouse::Button button)
{
  std::map<sf::Mouse::Button, unsigned int>::iterator iter = _actionMapMouse.find(button);
  if (iter != _actionMapMouse.end())
  {
    return iter->second;
  }
  return 0;
}

void ActionMapper::clearBinding(sf::Keyboard::Key key)
{
  _actionMapKeyboard.erase(key);
}
void ActionMapper::clearBinding(sf::Mouse::Button button)
{
  _actionMapMouse.erase(button);
}

void ActionMapper::clearAllBinding()
{
  _actionMapKeyboard.clear();
  _actionMapMouse.clear();
}
