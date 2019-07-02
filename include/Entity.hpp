/*
 * File: Entity.hpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 2:38:37 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "ReactionMapper.hpp"
#include <stack>
#include <SFML/Window/Event.hpp>

class Entity
{
public:
  Entity(void *);
  ~Entity();
  ReactionMapper *_reactionMapper;
};

#endif
