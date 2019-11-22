/*
 * File: ReactionMapper.cpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday September 5th 2019 1:35:28 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "ReactionMapper.hpp"

ReactionMapper::ReactionMapper(void *obj) : objThis(obj) {}
ReactionMapper::~ReactionMapper() {}

bool ReactionMapper::executeCallback(int action, sf::Event &ev)
{
  std::unordered_map<int, delegate>::iterator iter = _reactionMap.find(action);
  if (iter != _reactionMap.end())
  {
    return (iter->second(ev));
  }
  else
  {
    return true;
  }
}

void ReactionMapper::clearBinding(int action)
{
  _reactionMap.erase(action);
}

void ReactionMapper::clearAllBinding()
{
  _reactionMap.clear();
}
