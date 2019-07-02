/*
 * File: Entity.hpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 9:23:16 am
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
  ReactionMapper *_reactionMapper;
  Entity();
  ~Entity();

private:
};

#endif
