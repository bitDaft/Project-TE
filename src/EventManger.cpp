/*
 * File: EventManger.cpp
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday December 24th 2019 6:03:43 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "EventManager.hpp"

EventManager::EventManager()
{
}
EventManager::~EventManager()
{
}
bool EventManager::popEvent(Event *&event)
{
  if (!c_events.empty())
  {
    event = c_events.front();
    c_events.pop();
    return true;
  }
  return false;
}