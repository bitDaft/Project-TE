/*
 * File: InputManager.cpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 3:13:20 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "InputManager.hpp"

InputManager::InputManager(InputHandler *game, ActionMapper *aMap) : _actionMapper(aMap), _itemList(), gameEntity(game)
{
}
InputManager::~InputManager() {}
void InputManager::setActionMapper(ActionMapper *aMap)
{
  _actionMapper = aMap;
}
void InputManager::pushEntity(InputHandler *e)
{
  _itemList.push_back(e);
}
void InputManager::replaceEntity(InputHandler *e)
{
  popEntity();
  pushEntity(e);
}
void InputManager::popEntity()
{
  _itemList.pop_back();
}
void InputManager::processInputsEvent(sf::Event &e)
{
  int action = -1;
  switch (e.type)
  {
  case sf::Event::KeyPressed:
  case sf::Event::KeyReleased:
    action = _actionMapper->getBoundAction(e.key.code, e.type);
    break;
  case sf::Event::MouseButtonPressed:
  case sf::Event::MouseButtonReleased:
    action = _actionMapper->getBoundAction(e.mouseButton.button, e.type);
    break;
  case sf::Event::MouseMoved:
    action = _actionMapper->getBoundAction(sf::Mouse::Button(MOUSE_MOVE_BUTTON_VALUE), e.type);
    break;
  case sf::Event::MouseWheelMoved:
    action = _actionMapper->getBoundAction(sf::Mouse::Button(MOUSE_SCROLL_MOVE_BUTTON_VALUE), e.type);
    break;
  case sf::Event::MouseWheelScrolled:
    action = _actionMapper->getBoundAction(sf::Mouse::Button(MOUSE_SCROLL_BUTTON_VALUE), e.type);
    break;

  default:
    break;
  }
  if (action == -1)
    return;
  bool passThrough = true;
  for (std::vector<InputHandler *>::reverse_iterator it = _itemList.rbegin(); it != _itemList.rend(); ++it)
  {
    if (!((*it)->_reactionMapper->executeCallback(action, e)))
    {
      passThrough = false;
      break;
    }
  }
  if (passThrough)
  {
    gameEntity->_reactionMapper->executeCallback(action, e);
  }
}