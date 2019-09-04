/*
 * File: EventManager.inl
 * Project: Project-TE
 * Created Date: Friday August 30th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday September 4th 2019 1:17:08 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "EventManager.hpp"
#include "CEvent.hpp"

template <typename data_type>
void EventManager::pushEvent(int t, data_type *data)
{
  c_events.emplace(new CEVENT<data_type>(t, data));
}