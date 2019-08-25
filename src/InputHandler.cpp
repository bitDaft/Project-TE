/*
 * File: Entity.cpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday August 25th 2019 12:21:42 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "InputHandler.hpp"

InputHandler::InputHandler(void * obj)
{
  _reactionMapper = new ReactionMapper(obj);
}
InputHandler::~InputHandler() {
  delete _reactionMapper;
}