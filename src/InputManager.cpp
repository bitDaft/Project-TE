/*
 * File: InputManager.cpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Saturday, March 28th 2020 3:44:45 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "InputManager.hpp"

ActionMapper *InputManager::_actionMapper;
std::vector<InputHandler *> InputManager::_itemList;
InputHandler *InputManager::gameEntity = nullptr;

InputManager::InputManager(InputHandler *game)
{
  if (!gameEntity)
  {
    gameEntity = game;
  }
}
InputManager::~InputManager() {}
void InputManager::setActionMapper(ActionMapper *aMap)
{
  _actionMapper = aMap;
}

int InputManager::pushEntity(InputHandler *e)
{
  _itemList.push_back(e);
  return _itemList.size() - 1;
}
void InputManager::replaceEntity(InputHandler *e)
{
  if (_itemList.size())
    popEntity();
  pushEntity(e);
}
void InputManager::popEntity()
{
  if (_itemList.size())
    _itemList.pop_back();
}
void InputManager::removeEntity(int pos)
{
  _itemList[pos] = nullptr;
}
void InputManager::processInputsEvent(sf::Event &e)
{
  int action = -1;
  switch (e.type)
  {
  case sf::Event::KeyPressed:
  case sf::Event::KeyReleased:
    action = _actionMapper->getBoundAction(e.key.code, e.type);
    break;
  case sf::Event::MouseButtonPressed:
  case sf::Event::MouseButtonReleased:
    action = _actionMapper->getBoundAction(e.mouseButton.button, e.type);
    break;
  case sf::Event::MouseMoved:
  case sf::Event::MouseWheelMoved:
  case sf::Event::MouseWheelScrolled:
    action = _actionMapper->getBoundAction(sf::Mouse::Button(-1), e.type);
    break;

  default:
    break;
  }
  if (action == -1)
    return;
  bool passThrough = true;
  InputHandler *ih;
  for (std::vector<InputHandler *>::reverse_iterator it = _itemList.rbegin(); it != _itemList.rend(); ++it)
  {
    ih = *it;
    if (!ih || !ih->isHandling){
      continue;
    }
    if (!(ih->_reactionMapper->executeCallback(action, e)))
    {
      passThrough = false;
      break;
    }
  }
  if (passThrough)
  {
    gameEntity->_reactionMapper->executeCallback(action, e);
  }
}
void InputManager::clearEntity()
{
  _itemList.clear();
}