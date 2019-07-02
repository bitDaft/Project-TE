/*
 * File: ReactionMapper.cpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 8:36:38 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "ReactionMapper.hpp"

ReactionMapper::ReactionMapper(sf::RenderWindow &w, void *o) : wind(w), objThis(o) {}
ReactionMapper::~ReactionMapper() {}

void ReactionMapper::bindActionToReaction(unsigned int action, delegate callback)
{
  _reactionMap[action] = callback;
}

bool ReactionMapper::executeCallback(unsigned int action, sf::Event &ev)
{
  std::map<unsigned int, delegate>::iterator iter = _reactionMap.find(action);
  if (iter != _reactionMap.end())
  {
    return (iter->second(wind, ev));
  }
  return true;
}

void ReactionMapper::clearBinding(unsigned int key)
{
  _reactionMap.erase(key);
}

void ReactionMapper::clearAllBinding()
{
  _reactionMap.clear();
}
