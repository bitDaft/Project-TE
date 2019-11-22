/*
 * File: Entity.cpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday November 20th 2019 8:53:10 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "InputHandler.hpp"

InputHandler::InputHandler() : _reactionMapper(new ReactionMapper(this))
{
}
InputHandler::~InputHandler()
{
  delete _reactionMapper;
}