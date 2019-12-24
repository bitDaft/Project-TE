/*
 * File: EventProxy.hpp
 * Project: Project-TE
 * Created Date: Tuesday September 3rd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday December 24th 2019 6:03:43 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef EVENTPROXY_HPP
#define EVENTPROXY_HPP

#include <SFML/Window/Event.hpp>

#include "Event.hpp"

/**
 * Proxy class for events in use for CRTP
 */
template <typename derived>
class EventProxy : public Event
{
private:

  /**
   * Calls the derived classes clear function to clear up memory  
   * @return void
   */
  void clear();
  
  /**
   * Calls the derived classes prevent function to prevent clearing up of memory
   * @return void
   */
  void prevent();

public:

  // constructor destructor
  explicit EventProxy(int eventType);
  virtual ~EventProxy();
};

#include "EventProxy.inl"

#endif