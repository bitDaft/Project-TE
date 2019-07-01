/*
 * File: InputManager.cpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 2:17:35 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "InputManager.hpp"

InputManager::InputManager() : _actionMapper(0), _itemList() {}
InputManager::~InputManager() {}
void InputManager::setActionMapper(ActionMapper *aMap)
{
  _actionMapper = aMap;
}
void InputManager::processInputsRealtime() {}
void InputManager::processInputsEvent(sf::Event &e) {}