/*
 * File: ActionMapper.cpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 3:16:02 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "ActionMapper.hpp"

ActionMapper::ActionMapper() {}
ActionMapper::~ActionMapper() {}

void ActionMapper::bindInputToAction(sf::Keyboard::Key key, sf::Event::EventType type, unsigned int action)
{
  _actionMapKeyboard[{key, type}] = action;
}

void ActionMapper::bindInputToAction(sf::Mouse::Button button, sf::Event::EventType type, unsigned int action)
{
  _actionMapMouse[{button, type}] = action;
}

unsigned int ActionMapper::getBoundAction(sf::Keyboard::Key key, sf::Event::EventType type)
{

  std::map<std::pair<sf::Keyboard::Key, sf::Event::EventType>, unsigned int>::iterator iter = _actionMapKeyboard.find({key, type});
  if (iter != _actionMapKeyboard.end())
  {
    return iter->second;
  }
  return 0;
}

unsigned int ActionMapper::getBoundAction(sf::Mouse::Button button, sf::Event::EventType type)
{
  std::map<std::pair<sf::Mouse::Button, sf::Event::EventType>, unsigned int>::iterator iter = _actionMapMouse.find({button, type});
  if (iter != _actionMapMouse.end())
  {
    return iter->second;
  }
  return 0;
}

void ActionMapper::clearBinding(sf::Keyboard::Key key, sf::Event::EventType type)
{
  _actionMapKeyboard.erase({key, type});
}
void ActionMapper::clearBinding(sf::Mouse::Button button, sf::Event::EventType type)
{
  _actionMapMouse.erase({button, type});
}

void ActionMapper::clearAllBinding()
{
  _actionMapKeyboard.clear();
  _actionMapMouse.clear();
}
