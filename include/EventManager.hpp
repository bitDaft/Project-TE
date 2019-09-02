/*
 * File: EventManager.hpp
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Monday September 2nd 2019 6:07:04 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <queue>

#include <SFML/Window/Event.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "CEvent.hpp"

class EventManager : public sf::NonCopyable
{
public:
  EventManager();
  ~EventManager();

protected:
  template <typename tt>
  void pushEvent(sf::Event::EventType, tt *);

  bool popEvent(Event *&);

private:
  std::queue<Event *> c_events;
};

#include "EventManager.inl"

#endif