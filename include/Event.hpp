/*
 * File: Event.hpp
 * Project: Project-TE
 * Created Date: Tuesday September 3rd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday September 5th 2019 12:13:04 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef EVENT_HPP
#define EVENT_HPP

class Event
{
public:
  Event() {}
  Event(int);
  virtual ~Event();

  virtual void clear() = 0;   // release the memory, prevent leak
  virtual void prevent() = 0; // prevent release the memory

  template <typename V>
  bool getData(V &);

public:
  int type;
};

#include "Event.inl"

#endif