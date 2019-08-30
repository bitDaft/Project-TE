/*
 * File: CEvent.inl
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday August 30th 2019 10:07:13 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */
#include "CEvent.hpp"
#include <iostream>

#include "T_traits.hpp"

template <typename event_key, typename objType>
CEvent<event_key, objType>::CEvent(event_key k, objType d)
    : sf::Event(), type(k), data(d)
{
}

template <typename event_key, typename objType>
CEvent<event_key, objType>::~CEvent()
{
  // if (is_pointer<objType>::value)
  // {
  //   delete reinterpret_cast<objType>(data);
  // }
  std::cout << "\n ispointer : " << is_pointer<objType>::value;
  // type = 0;
}

template <typename event_key, typename objType>
objType CEvent<event_key, objType>::operator->()
{
  return data;
}
