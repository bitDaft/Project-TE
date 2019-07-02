/*
 * File: ReactionMapper.hpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 2:31:43 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef REACTIONMAPPER_HPP
#define REACTIONMAPPER_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include "Delegate.hpp"

template <typename T>
struct point_to_mem;

template <class C, typename T>
struct point_to_mem<T C::*>
{
  using member_type = T;
  using class_type = C;
};

class ReactionMapper : private sf::NonCopyable
{
public:
  ReactionMapper(void *);
  ~ReactionMapper();

  template <auto T>
  void bindActionToReaction(unsigned int action)
  {
    using className = typename point_to_mem<decltype(T)>::class_type;
    className *tthis = static_cast<className *>(objThis);
    _reactionMap[action] = delegate::from_method<className, T>(tthis);
  }
  bool executeCallback(unsigned int action, sf::Event &event);

  void clearBinding(unsigned int action);

  void clearAllBinding();

private:
  std::map<unsigned int, delegate> _reactionMap;
  void *objThis;
};

#endif