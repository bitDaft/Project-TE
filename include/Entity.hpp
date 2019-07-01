/*
 * File: Entity.hpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 2:48:59 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "ReactionMapper.hpp"
#include <stack>
#include <SFML/Window/Event.hpp>

class Entity : private sf::NonCopyable
{
public:
  ReactionMapper *react;
  Entity();
  ~Entity();

private:
};

#endif
