/*
 * File: ReactionMapper.cpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 1:48:00 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "ReactionMapper.hpp"

ReactionMapper::ReactionMapper(void *obj) : objThis(obj) {}
ReactionMapper::~ReactionMapper() {}

bool ReactionMapper::executeCallback(unsigned int action, sf::Event &ev)
{
  std::unordered_map<unsigned int, delegate>::iterator iter = _reactionMap.find(action);
  if (iter != _reactionMap.end())
  {
    return (iter->second(ev));
  }
  else
  {
    return true;
  }
}

void ReactionMapper::clearBinding(unsigned int action)
{
  _reactionMap.erase(action);
}

void ReactionMapper::clearAllBinding()
{
  _reactionMap.clear();
}
