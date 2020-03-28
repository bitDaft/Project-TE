/*
 * File: InputManager.hpp
 * Project: Project-TE
 * Created Date: Tuesday July 2nd 2019
 * Author: bitDaft
 * -----
 * Last Modified: Saturday, March 28th 2020 3:23:46 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */
#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <vector>
#include <SFML/Window/Event.hpp>

#include "ActionMapper.hpp"
#include "InputHandler.hpp"

/**
 * The input manager which checks the mapping of action from keys and calls the respective callback functions
 */
class InputManager : private sf::NonCopyable
{
public:
  InputManager(InputHandler *);
  ~InputManager();

  /**
   * Sets the action mapper pointer to another ActionMapper object
   * @param ActionMapper * The pointer to the new ActionMapper
   * @return void
   */
  static void setActionMapper(ActionMapper *);
  /**
   * Processes the inputs obtained from the event queue
   * @param sf::Event & The Event that was generated
   * @return void
   */
  static void processInputsEvent(sf::Event &);

  /**
   * Pushes an InputHandler object on to the daisy chain stack for callback evaluation
   * @param InputHandler * A pointer to the input handler object
   * @return void
   */
  static int pushEntity(InputHandler *);
  /**
   * Replaces an InputHandler object on top of the daisy chain stack for callback evaluation
   * @param InputHandler * A pointer to the input handler object to replace
   * @return void
   */
  static void replaceEntity(InputHandler *);
  /**
   * Removes the top InputHandler object  of the daisy chain stack for callback evaluation
   * @return void
   */
  static void popEntity();
  static void removeEntity(int);
  /**
   * clears the stack for callback evaluation
   * @return void
   */
  static void clearEntity();

private:
  static ActionMapper *_actionMapper;
  static std::vector<InputHandler *> _itemList;
  static InputHandler *gameEntity;
};

#endif