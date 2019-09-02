/*
 * File: Event.hpp
 * Project: Project-TE
 * Created Date: Wednesday August 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Monday September 2nd 2019 5:47:05 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef CEVENT_HPP
#define CEVENT_HPP

#include <SFML/Window/Event.hpp>

template <typename dataType>
class CEVENT;
class Event
{
private:
public:
  Event() {}
  Event(sf::Event::EventType);
  virtual ~Event();
  sf::Event::EventType type;
  virtual void clear() = 0;
  template <class data_type>
  operator data_type *();
  Event &getData();
};

template <typename derived>
class EventProxy : public Event
{
public:
  EventProxy(sf::Event::EventType);
  virtual ~EventProxy();
  void clear();
};

template <typename dataType>
class CEVENT : public EventProxy<CEVENT<dataType>>
{
public:
  CEVENT();
  CEVENT(sf::Event::EventType, dataType *);
  virtual ~CEVENT();

  dataType *getData();
  void clearT();

  sf::Event::EventType type;

private:
  dataType *data;
};

#include "CEvent.inl"

#endif