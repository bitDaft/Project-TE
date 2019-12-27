/*
 * File: Event.hpp
 * Project: Project-TE
 * Created Date: Tuesday September 3rd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:41:38 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef EVENT_HPP
#define EVENT_HPP

/**
 * A class to hold data related to custom events
 * This class is not intended to be subclassed
 */
class Event
{
public:
  // constructor destructor
  Event(int eventType);
  virtual ~Event();

  /**
   * Should not be overriden
   * Should only be called by the user
   * calls the clear function by the internal class which subclasses it  
   * @return void
   */
  virtual void clear() = 0; // release the memory, prevent leak

  /**
   * Should not be overriden
   * Should only be called by the user
   * calls the prevent function by the internal class which subclasses it  
   * @return void
   */
  virtual void prevent() = 0; // prevent release the memory

  /**
   * Obtains the data stored in this event
   * @template objectType the type of the object of the data to be obtained
   * @param obj reference to an object to return the data of the event to
   * @return void
   */
  template <typename objectType>
  bool getData(objectType &obj);

public:
  int type;
};

#include "Event.inl"

#endif