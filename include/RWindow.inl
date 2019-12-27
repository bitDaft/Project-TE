/*
 * File: RWindow.inl
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:41:38 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "RWindow.hpp"
#include "T_traits.hpp"

template <class objType>
void RWindow::triggerEvent(int eventType, objType data)
{
  processEvents();
  using type = typename is_pointer<objType>::class_type;
  pushEvent<type>(eventType, data);
}
