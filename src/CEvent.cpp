/*
 * File: Event.cpp
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Monday September 2nd 2019 5:38:12 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "CEvent.hpp"

Event::Event(sf::Event::EventType v) : type(v)
{
}

Event::~Event()
{
}

Event &Event::getData()
{
  return *this;
}