/*
 * File: RWindow.inl
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday September 4th 2019 1:23:36 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "RWindow.hpp"
#include "T_traits.hpp"

template <class objType>
void RWindow::triggerEvent(int e, objType o)
{
  processEvents();
  using type = typename is_pointer<objType>::class_type;
  pushEvent<type>(e, o);
}