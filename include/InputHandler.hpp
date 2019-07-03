/*
 * File: Entity.hpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 3:26:28 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include "ReactionMapper.hpp"

/**
 * Inheriting from this class denotes the class as one that react to inputs
 * and can be used in callback stack of input manager
 */
class InputHandler
{
public:
  /**
   * constructor which initializes _reactionMapper
   * @param void* pointer to the inheriting object, normally `this`
   */
  InputHandler(void *);
  ~InputHandler();
  ReactionMapper *_reactionMapper;
};

#endif
