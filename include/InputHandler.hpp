/*
 * File: Entity.hpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 2:35:52 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include "ReactionMapper.hpp"
#include <stack>
#include <SFML/Window/Event.hpp>

class InputHandler
{
public:
  InputHandler(void *);
  ~InputHandler();
  ReactionMapper *_reactionMapper;
};

#endif
