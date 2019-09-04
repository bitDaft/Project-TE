/*
 * File: Event.hpp
 * Project: Project-TE
 * Created Date: Wednesday August 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday September 5th 2019 12:04:21 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef CEVENT_HPP
#define CEVENT_HPP

#include "Event.hpp"
#include "EventProxy.hpp"

template <typename dataType>
class CEVENT : public EventProxy<CEVENT<dataType>>
{
public:
  CEVENT();
  CEVENT(int, dataType *);
  virtual ~CEVENT();

private:
  friend class Event;
  friend class EventProxy<CEVENT<dataType>>;
  dataType *getData();
  void clearT();
  void preventT();
  dataType *data;
  bool preventClear;
};

#include "CEvent.inl"

#endif