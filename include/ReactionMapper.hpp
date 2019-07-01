/*
 * File: ReactionMapper.hpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 2:02:40 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef REACTIONMAPPER_HPP
#define REACTIONMAPPER_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include "Delegate.hpp"

template <typename T>
struct point_to_mem;

// Meta-function to extract type information from a pointer to a member.
template <class C, typename T>
struct point_to_mem<T C::*>
{
  using member_type = T;
  using class_type = C;
};

class ReactionMapper : private sf::NonCopyable
{
public:
  ReactionMapper(sf::RenderWindow &, void *);
  ~ReactionMapper();

  template <auto T>
  void bindActionToReaction(unsigned int action)
  {
    using className = typename point_to_mem<decltype(T)>::class_type;
    className *tthis = static_cast<className *>(objThis);
    _reactionMap[action] = delegate::from_method<className, T>(tthis);
  }
  void bindActionToReaction(unsigned int action, delegate callback);
  void executeCallback(unsigned int action, sf::Event &event);

  void clearBinding(unsigned int key);

  void clearAllBinding();

private:
  std::map<unsigned int, delegate> _reactionMap;
  sf::RenderWindow &wind;
  void *objThis;
};

#endif