/*
 * File: Event.inl
 * Project: Project-TE
 * Created Date: Tuesday September 3rd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday December 24th 2019 6:10:21 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "Event.hpp"
#include "CEvent.hpp"

template <typename objectType>
bool Event::getData(objectType &obj)
{
  CEVENT<objectType> *e = dynamic_cast<CEVENT<objectType> *>(this);
  if (!e)
    return false;
  obj = *(e->getData());
  return true;
}