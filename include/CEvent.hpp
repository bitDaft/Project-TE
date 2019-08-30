/*
 * File: Event.hpp
 * Project: Project-TE
 * Created Date: Wednesday August 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday August 30th 2019 9:55:16 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef CEVENT_HPP
#define CEVENT_HPP

#include <SFML/Window/Event.hpp>
#include <unordered_map>

// ?template it so it can be initialized with the enum values given from user
template <typename event_key, typename objType = void *>
class CEvent : public sf::Event
{
public:
  // !this should copy over the original value of the event type if not a custom eventso as to not break
  // ?should we though.. nope dont think so
  // !since the original is not enum class we can simply continue using unsigned int
  // !the custom enum list will have to intialise the first value to sf::Event::Count + 1
  CEvent(event_key, objType = NULL);
  virtual ~CEvent();

  objType operator->();

  // ^we need a way to create new event type keys
  // ?part of custom window
  // ^need a way to associate arbitrary data with event type
  // ^need to override the interface of base sf::Event
  // ^since the base Event does not have any method and allows direct access to
  event_key type;

private:
  objType data;
};

#include "CEvent.inl"

#endif