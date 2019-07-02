/*
 * File: InputManager.cpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 9:51:30 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "InputManager.hpp"

InputManager::InputManager(Entity *game) : _actionMapper(0), _itemList()
{
  gameEntity = game;
}
InputManager::~InputManager() {}
void InputManager::setActionMapper(ActionMapper *aMap)
{
  _actionMapper = aMap;
}
void InputManager::pushEntity(Entity *e)
{
  _itemList.push_back(e);
}
void InputManager::replaceEntity(Entity *e)
{
  popEntity();
  pushEntity(e);
}
void InputManager::popEntity()
{
  _itemList.pop_back();
}
void InputManager::processInputsRealtime() {}
void InputManager::processInputsEvent(sf::Event &e)
{
  unsigned int t = _actionMapper->getBoundAction(e.key.code);
  for (auto entity : _itemList)
  {
    if (!(entity->_reactionMapper->executeCallback(t, e)))
    {
      break;
    }
  }
  gameEntity->_reactionMapper->executeCallback(t, e);
}