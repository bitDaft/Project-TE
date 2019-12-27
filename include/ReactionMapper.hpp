/*
 * File: ReactionMapper.hpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:41:38 am
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

#include "T_traits.hpp"

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
  explicit ReactionMapper(void *);
  virtual ~ReactionMapper();

  /**
   * Templated function which recieves the function and the pointer to the executing object
   * @template T The callback member function 
   * @param int The action to which the callback is bound 
   * @return void
   */
  template <auto T>                     // ^C++17 feature, using auto in template
  void bindActionToReaction(int action) // ?Move it into an inline file
  {
    using className = typename point_to_mem<decltype(T)>::class_type;
    className *tthis = static_cast<className *>(objThis);
    _reactionMap[action] = delegate::from_method<className, T>(tthis);
  }
  /**
   * Execute tha callback function associated with the action
   * @param int The action to execute callback for
   * @param sf::Event & The event that was generated 
   * @return bool whether to continue the daisy chain or stop
   */
  bool executeCallback(int action, sf::Event &event);

  /**
   * Clear the callback binding related to the action
   * @param int The action to clear the callback for
   * @return void
   */
  void clearBinding(int action);

  /**
   * Clear all callback binding 
   * @return void
   */
  void clearAllBinding();

private:
  std::unordered_map<int, delegate> _reactionMap;
  void *objThis;
};

#endif