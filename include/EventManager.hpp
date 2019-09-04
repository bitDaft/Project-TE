/*
 * File: EventManager.hpp
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday September 4th 2019 1:17:08 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <queue>

#include <SFML/Window/Event.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "Event.hpp"

class EventManager : public sf::NonCopyable
{
public:
  EventManager();
  ~EventManager();

protected:
  template <typename data_type>
  void pushEvent(int, data_type *);

  bool popEvent(Event *&);

private:
  // class EventManagerImpl;
  // EventManagerImpl *impl;

  std::queue<Event *> c_events;
};

#include "EventManager.inl"

#endif