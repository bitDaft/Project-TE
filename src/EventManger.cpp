/*
 * File: EventManger.cpp
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday September 5th 2019 1:51:26 pm
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