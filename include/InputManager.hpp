/*
 * File: InputManager.hpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 5:26:36 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */
#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "ActionMapper.hpp"
#include <vector>
#include <SFML/Window/Event.hpp>
#include <Entity.hpp>

class InputManager : private sf::NonCopyable
{
public:
  InputManager(Entity *, ActionMapper *);
  ~InputManager();

  void setActionMapper(ActionMapper *);
  void processInputsRealtime();
  void processInputsEvent(sf::Event &);

  void pushEntity(Entity *);
  void replaceEntity(Entity *);
  void popEntity();

private:
  ActionMapper *_actionMapper;
  std::vector<Entity *> _itemList;
  Entity *gameEntity;
};

#endif