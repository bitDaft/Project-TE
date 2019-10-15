/*
 * File: EventProxy.inl
 * Project: Project-TE
 * Created Date: Tuesday September 3rd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday October 15th 2019 11:38:54 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "EventProxy.hpp"

template <typename derived>
EventProxy<derived>::EventProxy(int v) : Event(v)
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
  delete p;
}
template <typename derived>
void EventProxy<derived>::prevent()
{
  derived *p = static_cast<derived *>(this);
  p->preventT();
}