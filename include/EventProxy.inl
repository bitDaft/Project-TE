/*
 * File: EventProxy.inl
 * Project: Project-TE
 * Created Date: Tuesday September 3rd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday, March 25th 2020 8:27:04 am
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "EventProxy.hpp"

template <typename derived>
EventProxy<derived>::EventProxy(int eventType) : Event(eventType)
{
}

template <typename derived>
EventProxy<derived>::~EventProxy()
{
}

template <typename derived>
void EventProxy<derived>::clear()
{
  derived *p = static_cast<derived *>(this);
  p->clearT();
  // delete p;
}
template <typename derived>
void EventProxy<derived>::prevent()
{
  derived *p = static_cast<derived *>(this);
  p->preventT();
}