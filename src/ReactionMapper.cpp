/*
 * File: ReactionMapper.cpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Monday July 1st 2019 6:03:44 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "ReactionMapper.hpp"
#include <iostream>

ReactionMapper::ReactionMapper(sf::RenderWindow &w) : wind(w) {}
ReactionMapper::~ReactionMapper() {}

// void ReactionMapper::bindActionToReaction(unsigned int action, void (*callback)(sf::RenderWindow &, sf::Event &))
void ReactionMapper::bindActionToReaction(unsigned int action, delegate callback)
{
  // auto c = []() { std::cout << "a"; };
  // auto thunk = [](void *arg) { // note thunk is captureless
  //   (*static_cast<decltype(c) *>(arg))();
  // };
  // thunk(callback);
  _reactionMap[action] = callback;
}

void ReactionMapper::executeCallback(unsigned int action, sf::Event &ev)
{
  std::map<unsigned int, delegate>::iterator iter = _reactionMap.find(action);
  if (iter != _reactionMap.end())
  {
    iter->second(wind, ev);
  }
}

// unsigned int ActionMapper::getBoundAction(sf::Keyboard::Key key)
// {
// }

// unsigned int ActionMapper::getBoundAction(sf::Mouse::Button button)
// {
//   std::map<sf::Mouse::Button, unsigned int>::iterator iter = _actionMapMouse.find(button);
//   if (iter != _actionMapMouse.end())
//   {
//     return iter->second;
//   }
//   return 0;
// }

void ReactionMapper::clearBinding(unsigned int key)
{
  _reactionMap.erase(key);
}

void ReactionMapper::clearAllBinding()
{
  _reactionMap.clear();
}
