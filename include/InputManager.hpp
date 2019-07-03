/*
 * File: InputManager.hpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 2:38:59 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */
#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "ActionMapper.hpp"
#include <vector>
#include <SFML/Window/Event.hpp>
#include "InputHandler.hpp"

class InputManager : private sf::NonCopyable
{
public:
  InputManager(InputHandler *, ActionMapper *);
  ~InputManager();

  void setActionMapper(ActionMapper *);
  void processInputsRealtime();
  void processInputsEvent(sf::Event &);

  void pushEntity(InputHandler *);
  void replaceEntity(InputHandler *);
  void popEntity();

private:
  ActionMapper *_actionMapper;
  std::vector<InputHandler *> _itemList;
  InputHandler *gameEntity;
};

#endif