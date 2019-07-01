/*
 * File: InputManager.cpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 2:45:35 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "InputManager.hpp"

InputManager::InputManager(Entity *game) : _actionMapper(0), _itemList() {
  _itemList.push_back(std::make_shared<Entity>(game));
}
InputManager::~InputManager() {}
void InputManager::setActionMapper(ActionMapper *aMap)
{
  _actionMapper = aMap;
}
void InputManager::processInputsRealtime() {}
void InputManager::processInputsEvent(sf::Event::KeyEvent &e) {
  unsigned int t = _actionMapper->getBoundAction(e.code);
  for(auto entity : _itemList)
  {
  }
}