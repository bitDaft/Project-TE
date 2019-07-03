/*
 * File: ActionMapper.hpp
 * Project: Project-TE
 * Created Date: Friday June 28th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 2:19:52 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef ACTIONMAPPER_HPP
#define ACTIONMAPPER_HPP

#define MOUSE_MOVE_BUTTON_VALUE 999
#define MOUSE_SCROLL_BUTTON_VALUE 998
#define MOUSE_SCROLL_MOVE_BUTTON_VALUE 997

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <unordered_map>

namespace std
{
template <>
struct hash<pair<sf::Mouse::Button, sf::Event::EventType>>
{
  size_t operator()(const pair<sf::Mouse::Button, sf::Event::EventType> &k) const
  {
    return (17 * 31 + hash<sf::Mouse::Button>()(k.first)) * 31 + hash<sf::Event::EventType>()(k.second);
  }
};
template <>
struct hash<pair<sf::Keyboard::Key, sf::Event::EventType>>
{
  size_t operator()(const pair<sf::Keyboard::Key, sf::Event::EventType> &k) const
  {
    return (17 * 31 + hash<sf::Keyboard::Key>()(k.first)) * 31 + hash<sf::Event::EventType>()(k.second);
  }
};
} // namespace std

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
  // ^Moved to private for internal use while parsing of the file later

  void bindInputToAction(sf::Keyboard::Key key, sf::Event::EventType type, unsigned int action);
  void bindInputToAction(sf::Mouse::Button button, sf::Event::EventType type, unsigned int action);
  void bindInputToAction(sf::Event::EventType type, unsigned int action);

  int getBoundAction(sf::Keyboard::Key key, sf::Event::EventType type);
  int getBoundAction(sf::Mouse::Button button, sf::Event::EventType type);

  void clearBinding(sf::Keyboard::Key key, sf::Event::EventType type);
  void clearBinding(sf::Mouse::Button button, sf::Event::EventType type);

  void clearAllBinding();

private:
  // TODO:Test map vs unordered map to find speed diff, after coverting to data config read , whether it is usefull or not
  std::unordered_map<std::pair<sf::Keyboard::Key, sf::Event::EventType>, unsigned int> _actionMapKeyboard;
  std::unordered_map<std::pair<sf::Mouse::Button, sf::Event::EventType>, unsigned int> _actionMapMouse;
};

#endif