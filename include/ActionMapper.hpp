/*
 * File: ActionMapper.hpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 4:26:45 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef ACTIONMAPPER_HPP
#define ACTIONMAPPER_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
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

  void bindInputToAction(sf::Keyboard::Key key, sf::Event::EventType type, unsigned int action);
  void bindInputToAction(sf::Mouse::Button button, sf::Event::EventType type, unsigned int action);

  int getBoundAction(sf::Keyboard::Key key, sf::Event::EventType type);
  int getBoundAction(sf::Mouse::Button button, sf::Event::EventType type);

  void clearBinding(sf::Keyboard::Key key, sf::Event::EventType type);
  void clearBinding(sf::Mouse::Button button,sf::Event::EventType type);

  void clearAllBinding();

private:
  // ?Change from map to unordered map as the insertion or such operations ate only
  // ?Done at the begining or very rarely, once the control scheme has been set ,
  // ?The frequency of change in key bindings is very low
  // ?So lookup time can be prioritzed to be faster at the cost of memory
  // TODO:Test this vs unordered map to find speed diff, after coverting to data config read
  std::map<std::pair<sf::Keyboard::Key, sf::Event::EventType>, unsigned int> _actionMapKeyboard;
  std::map<std::pair<sf::Mouse::Button, sf::Event::EventType>, unsigned int> _actionMapMouse;
};

#endif