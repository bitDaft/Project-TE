/*
 * File: EventManger.cpp
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Monday September 2nd 2019 5:49:44 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "EventManager.hpp"
#include "CEvent.hpp"
#include "test.hpp"
#include <iostream>

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