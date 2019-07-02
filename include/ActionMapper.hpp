/*
 * File: ActionMapper.hpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday June 28th 2019 1:53:16 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef ACTIONMAPPER_HPP
#define ACTIONMAPPER_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <map>

class ActionMapper : private sf::NonCopyable
{
public:
  ActionMapper();
  ~ActionMapper();

  // ^Currently the binding have to be defined one by one
  // ^Change it to load from a config data file
  // ^This will allow us to load from file for controls
  // ^In case of control mapping change just reload with the file again instead
  // ^This change will cause many of these function to change over time
  // ^Probably will have to get rid of it and just have a load from file function
  // ^And an unload or destroy mapping function
  // ^Moved to private for internal use while parsing of the file

  void bindInputToAction(sf::Keyboard::Key key, unsigned int action);
  void bindInputToAction(sf::Mouse::Button button, unsigned int action);

  unsigned int getBoundAction(sf::Keyboard::Key key);
  unsigned int getBoundAction(sf::Mouse::Button button);

  void clearBinding(sf::Keyboard::Key key);
  void clearBinding(sf::Mouse::Button button);

  void clearAllBinding();

private:

  // ?Change from map to unordered map as the insertion or such operations ate only
  // ?Done at the begining or very rarely, once the control scheme has been set ,
  // ?The frequency of change in key bindings is very low
  // ?So lookup time can be prioritzed to be faster at the cost of memory
  // TODO:Test this vs unordered map to find speed diff, after coverting to data config read

  std::map<sf::Keyboard::Key, unsigned int> _actionMapKeyboard;
  std::map<sf::Mouse::Button, unsigned int> _actionMapMouse;
};

#endif