/*
 * File: Entity.cpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Saturday, March 28th 2020 3:42:59 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "InputHandler.hpp"
#include "InputManager.hpp"

InputHandler::InputHandler()
    : _reactionMapper(new ReactionMapper(this)),
      isHandling(true),
      _2(-1)
{
}
InputHandler::~InputHandler()
{
  delete _reactionMapper;
}

void InputHandler::enableInputHandling()
{
  if (!~_2)
  {
    _2 = InputManager::pushEntity(this);
  }
  isHandling = true;
}
void InputHandler::disableInputHandling()
{
  isHandling = false;
}
void InputHandler::removeInputHandling()
{
  if (~_2)
  {
    InputManager::removeEntity(_2);
  }
  _2 = -1;
}