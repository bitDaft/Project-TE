/*
 * File: EventManager.inl
 * Project: Project-TE
 * Created Date: Friday August 30th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Monday September 2nd 2019 6:07:04 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "EventManager.hpp"

template <typename data_type>
void EventManager::pushEvent(sf::Event::EventType t, data_type *data)
{
  CEVENT<data_type> *ce = new CEVENT<data_type>(t, data);
  c_events.push(ce);
}