/*
 * File: Event.inl
 * Project: Project-TE
 * Created Date: Tuesday September 3rd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday September 4th 2019 12:51:22 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "Event.hpp"
#include "CEvent.hpp"

template <typename V>
bool Event::getData(V &v)
{
  CEVENT<V> *e = dynamic_cast<CEVENT<V> *>(this);
  if (!e)
    return false;
  v = *(e->getData());
  return true;
}