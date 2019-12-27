/*
 * File: Event.hpp
 * Project: Project-TE
 * Created Date: Wednesday August 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:41:38 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef CEVENT_HPP
#define CEVENT_HPP

#include "Event.hpp"
#include "EventProxy.hpp"

/**
 * A class that holds the actual data of the event
 * This class is not intended to be subclassed
 */
template <typename dataType>
class CEVENT : public EventProxy<CEVENT<dataType>>
{
public:
  // constructor destructor
  CEVENT();
  CEVENT(int eventType, dataType *data);
  virtual ~CEVENT();

private:
  friend class Event;
  friend class EventProxy<CEVENT<dataType>>;

  /**
   * Obtains the pointer to the data stored for this event
   * @return void
   */
  dataType *getData();

  /**
   * clears the memory used to store the data
   * @return void
   */
  void clearT();

  /**
   * prevetns clearing the memory used to store the data
   * @return void
   */
  void preventT();

  dataType *data;
  bool preventClear;
};

#include "CEvent.inl"

#endif