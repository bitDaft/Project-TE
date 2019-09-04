/*
 * File: EventProxy.hpp
 * Project: Project-TE
 * Created Date: Tuesday September 3rd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday September 5th 2019 12:04:21 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef EVENTPROXY_HPP
#define EVENTPROXY_HPP

#include <SFML/Window/Event.hpp>

#include "Event.hpp"

template <typename derived>
class EventProxy : public Event
{
private:
  void clear();
  void prevent();

public:
  EventProxy(int);
  virtual ~EventProxy();
};

#include "EventProxy.inl"

#endif