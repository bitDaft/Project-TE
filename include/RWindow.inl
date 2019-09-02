/*
 * File: RWindow.inl
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Monday September 2nd 2019 6:16:18 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "RWindow.hpp"
#include "T_traits.hpp"

template <typename event_key, class objType = void *>
void RWindow::triggerEvent(event_key e, objType o)
{
  processEvents();
  using type = typename is_pointer<objType>::class_type;
  pushEvent<type>((sf::Event::EventType)e, o);
}
