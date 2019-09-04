/*
 * File: EventManger.cpp
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday September 4th 2019 11:52:37 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "EventManager.hpp"
#include "EventManagerImpl.hpp"

EventManager::EventManager()
// : impl(new EventManagerImpl())
{
}
EventManager::~EventManager()
{
  // delete impl;
}
bool EventManager::popEvent(Event *&e)
{
  if (!c_events.empty())
  {
    e = c_events.front();
    c_events.pop();
    return true;
  }
  return false;
}