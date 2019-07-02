/*
 * File: ReactionMapper.cpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 11:29:29 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "ReactionMapper.hpp"

ReactionMapper::ReactionMapper(sf::RenderWindow &w, void *o) : wind(w), objThis(o) {}
ReactionMapper::~ReactionMapper() {}

bool ReactionMapper::executeCallback(unsigned int action, sf::Event &ev)
{
  std::map<unsigned int, delegate>::iterator iter = _reactionMap.find(action);
  if (iter != _reactionMap.end())
  {
    return (iter->second(wind, ev));
  }
  else
  {
    return true;
  }
}

void ReactionMapper::clearBinding(unsigned int key)
{
  _reactionMap.erase(key);
}

void ReactionMapper::clearAllBinding()
{
  _reactionMap.clear();
}
