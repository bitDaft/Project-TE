/*
 * File: CEvent.inl
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

template <typename dataType>
CEVENT<dataType>::CEVENT() : EventProxy<CEVENT<dataType>>((sf::Event::EventType)(-1)),
                             type((sf::Event::EventType)(-1)),
                             data(NULL)
{
}

template <typename dataType>
CEVENT<dataType>::CEVENT(sf::Event::EventType t, dataType *d) : EventProxy<CEVENT<dataType>>(t),
                                                                type(t),
                                                                data(d)
{
}

template <typename dataType>
CEVENT<dataType>::~CEVENT()
{
  type = (sf::Event::EventType)(-1);
  data = NULL;
}

template <typename dataType>
dataType *CEVENT<dataType>::getData()
{
  return data;
}

template <typename dataType>
void CEVENT<dataType>::clearT()
{
  delete data;
}

template <typename derived>
EventProxy<derived>::EventProxy(sf::Event::EventType v) : Event(v)
{
}

template <typename derived>
EventProxy<derived>::~EventProxy()
{
}

template <typename derived>
void EventProxy<derived>::clear()
{
  derived *p = dynamic_cast<derived *>(this);
  p->clearT();
}

template <class data_type>
Event::operator data_type *()
{
  CEVENT<data_type> *e = static_cast<CEVENT<data_type> *>(this);
  if (!e)
    return nullptr;
  return e->getData();
}

