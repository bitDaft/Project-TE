/*
 * File: EventManager.hpp
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:41:38 am
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

/**
 * Manages and processes custom events in the event queue
 */
class EventManager : public sf::NonCopyable
{
public:
  // constructor destructor
  EventManager();
  ~EventManager();

protected:
  /**
   * Pushes a new event into the queue  
   * @template data_type the data type of the data
   * @param eventType the type of the event
   * @param data pointer to the data
   * @return void
   */
  template <typename data_type>
  void pushEvent(int eventType, data_type *data);

  /**
   * Obtains and pops an event from the event queue    
   * @param event refernce to a pointer to the popped event
   * @return bool whether an event was successfully obtained
   */
  bool popEvent(Event *&event);

private:
  std::queue<Event *> c_events;
};

#include "EventManager.inl"

#endif