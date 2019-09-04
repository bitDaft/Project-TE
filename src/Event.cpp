/*
 * File: Event.cpp
 * Project: Project-TE
 * Created Date: Tuesday September 3rd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday September 4th 2019 1:17:08 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "Event.hpp"
#include "EventImpl.hpp"

Event::Event(int v) : type(v)
// , impl(new EventImpl())
{
}

Event::~Event()
{
  // delete impl;
}