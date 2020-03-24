/*
 * File: Entity.hpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday, March 24th 2020 1:45:13 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
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
  // ^ the inputmanager needs it to be public so it can call the executecallback function
  // ? can we make this a friend of inputmanager so as to be able to access it
  // ^ Nah.. i think this is fine. if the y break. they break;
  ReactionMapper *_reactionMapper;
};

#endif
