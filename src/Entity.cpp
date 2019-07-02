/*
 * File: Entity.cpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 2:04:46 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Entity.hpp"

Entity::Entity(void * obj)
{
  _reactionMapper = new ReactionMapper(obj);
}
Entity::~Entity() {
  delete _reactionMapper;
}