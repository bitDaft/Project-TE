/*
 * File: Entity.hpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday December 24th 2019 5:52:32 pm
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
  // constructor destructor
  InputHandler();
  virtual ~InputHandler();

  // ?why is this public
  // ?check out why it is public and why it cant be made private
  // TODO: create a delegate function for the needed function from this object 
  ReactionMapper *_reactionMapper;
};

#endif
