/*
 * File: ReactionMapper.hpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 1:11:45 am
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
#include <functional>
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
  ReactionMapper(sf::RenderWindow &);
  ~ReactionMapper();

  // ^No idea what a input callback function is supposed to do though

  // void bindActionToReaction(unsigned int action, void (*callback)(sf::RenderWindow &, sf::Event &));
  // template <typename T>
  // void bindActionToReaction1(unsigned int action, void *t)
  // {
  //   using className = typename point_to_mem<T>::class_type;
  //   bindActionToReaction4<decltype(T), T>(action, t);
  // }
  // template <class T, void (T::*TMethod)(sf::RenderWindow &, sf::Event &)>
  // void bindActionToReaction2(unsigned int action, T *callback)
  // {
  //   _reactionMap[action] = delegate::from_method<T, TMethod>(callback);
  // }
  template <auto T>
  void bindActionToReaction(unsigned int action, void *t)
  {
    using className = typename point_to_mem<decltype(T)>::class_type;
    className *tthis = static_cast<className *>(t);
    _reactionMap[action] = delegate::from_method<className, T>(tthis);
  }
  void bindActionToReaction(unsigned int action, delegate callback);
  void executeCallback(unsigned int action, sf::Event &event);

  void clearBinding(unsigned int key);

  void clearAllBinding();

private:
  // !-THINK THIS THROUGH AGAIN.... THIS CLASS WAS IMPLEMENTED ON A WHIM

  std::map<unsigned int, delegate> _reactionMap;
  sf::RenderWindow &wind;
  void *obj;
};

#endif