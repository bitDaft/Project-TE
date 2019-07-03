/*
 * File: Entity.cpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 2:39:00 pm
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