/*
 * File: EventProxy.inl
 * Project: Project-TE
 * Created Date: Tuesday September 3rd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday September 5th 2019 12:04:21 am
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
}
template <typename derived>
void EventProxy<derived>::prevent()
{
  derived *p = static_cast<derived *>(this);
  p->preventT();
}