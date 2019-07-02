/*
 * File: InputManager.cpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 2:01:58 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "InputManager.hpp"

InputManager::InputManager(Entity *game, ActionMapper *aMap) : _itemList(), _actionMapper(aMap)
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
  int action = _actionMapper->getBoundAction(e.key.code, e.type);
  if (action == -1)
    return;
  bool passThrough = true;
  for (std::vector<Entity *>::reverse_iterator it = _itemList.rbegin(); it != _itemList.rend(); ++it)
  {
    if (!((*it)->_reactionMapper->executeCallback(action, e)))
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