/*
 * File: RWindow.hpp
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday September 4th 2019 1:23:36 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef RWINDOW_HPP
#define RWINDOW_HPP

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.hpp"
#include "Event.hpp"

class RWindow : public sf::RenderWindow, public EventManager
{
public:
  RWindow();
  RWindow(sf::VideoMode, const sf::String &, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings &settings = sf::ContextSettings());
  explicit RWindow(sf::WindowHandle handle, const sf::ContextSettings &settings = sf::ContextSettings());
  virtual ~RWindow();

  template < typename objType = void *>
  void triggerEvent(int, objType = NULL);

  bool pollEvent(Event *&);

private:
  void processEvents();
};

#include "RWindow.inl"

#endif