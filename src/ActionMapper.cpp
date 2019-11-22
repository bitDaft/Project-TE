/*
 * File: ActionMapper.cpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday September 5th 2019 1:37:30 pm
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
void ActionMapper::bindInputToAction(sf::Event::EventType type, unsigned int action)
{
  switch (type)
  {
  case sf::Event::MouseMoved:
  case sf::Event::MouseWheelMoved:
  case sf::Event::MouseWheelScrolled:
    bindInputToAction(sf::Mouse::Button(-1), type, action);
    break;
  default:
    break;
  }
}

int ActionMapper::getBoundAction(sf::Keyboard::Key key, sf::Event::EventType type)
{
  std::unordered_map<std::pair<sf::Keyboard::Key, sf::Event::EventType>, unsigned int>::iterator iter = _actionMapKeyboard.find({key, type});
  if (iter != _actionMapKeyboard.end())
  {
    return iter->second;
  }
  return -1;
}

int ActionMapper::getBoundAction(sf::Mouse::Button button, sf::Event::EventType type)
{
  std::unordered_map<std::pair<sf::Mouse::Button, sf::Event::EventType>, unsigned int>::iterator iter = _actionMapMouse.find({button, type});
  if (iter != _actionMapMouse.end())
  {
    return iter->second;
  }
  return -1;
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
