/*
 * File: ReactionMapper.hpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 3:26:28 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef REACTIONMAPPER_HPP
#define REACTIONMAPPER_HPP

#include <unordered_map>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Delegate.hpp"

/**
 * A templated class used for member function trait extraction
 */
template <typename T>
struct point_to_mem;

/**
 * A templated class used for member function trait extraction
 */
template <class C, typename T>
struct point_to_mem<T C::*>
{
  using member_type = T;
  using class_type = C;
};

/**
 * Holds the callback functions to each Action that has been mapped
 */
class ReactionMapper : private sf::NonCopyable
{
public:
  /**
   * Constructor initialise the callback object
   * @param void* The object whose member function are going to be callback functions 
   */
  ReactionMapper(void *);
  ~ReactionMapper();

  /**
   * Templated function with recieves the function and the pointer to the executing object
   * @template T The callback member function 
   * @param unsigned int The action to which the callback is bound 
   * @return void
   */
  template <auto T>
  void bindActionToReaction(unsigned int action)
  {
    using className = typename point_to_mem<decltype(T)>::class_type;
    className *tthis = static_cast<className *>(objThis);
    _reactionMap[action] = delegate::from_method<className, T>(tthis);
  }
  /**
   * Execute tha callback function associated with the action
   * @param unsigned int The action to execute callback for
   * @param sf::Event & The event that was generated 
   * @return bool whether to continue the daisy chain or stop
   */
  bool executeCallback(unsigned int action, sf::Event &event);

  /**
   * Clear the callback binding related to the action
   * @param unsigned int The action to clear the callback for
   * @return void
   */
  void clearBinding(unsigned int action);

  /**
   * Clear all callback binding 
   * @return void
   */
  void clearAllBinding();

private:
  std::unordered_map<unsigned int, delegate> _reactionMap;
  void *objThis;
};

#endif