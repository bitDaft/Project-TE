/*
 * File: RWindow.hpp
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Monday September 2nd 2019 6:16:18 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef RWINDOW_HPP
#define RWINDOW_HPP

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.hpp"
#include "CEvent.hpp"

class RWindow : public sf::RenderWindow, public EventManager
{
public:
  RWindow();
  RWindow(sf::VideoMode, const sf::String &, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings &settings = sf::ContextSettings());
  explicit RWindow(sf::WindowHandle handle, const sf::ContextSettings &settings = sf::ContextSettings());
  virtual ~RWindow();

  // ^allow for triggering event and passing data
  // ^should poll previous events into new queue
  template <typename event_key, typename objType = void *>
  void triggerEvent(event_key, objType = NULL);

  bool pollEvent(Event *&);

private:
  void processEvents();
  EventManager *eMan;
};

#include "RWindow.inl"

#endif