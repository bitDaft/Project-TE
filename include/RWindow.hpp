/*
 * File: RWindow.hpp
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:41:38 am
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

/** 
 * This is a specialization of RenderWindow to allow support for custom events
 * ^ It follows the pattern of RenderWindow class
 * ^ Inherits from base RenderWindow and Custom EventManager
*/
class RWindow : public sf::RenderWindow, public EventManager
{
public:
  // constructor and destructor
  RWindow();
  RWindow(sf::VideoMode, const sf::String &, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings &settings = sf::ContextSettings());
  explicit RWindow(sf::WindowHandle handle, const sf::ContextSettings &settings = sf::ContextSettings());
  virtual ~RWindow();

  /**
   * Trigger and add a new event to the event queue   
   * @template objType This is the type of the pointer to data
   * @param eventType This is type of the event
   * @param data This is the pointer to the data
   * @return void
   */
  template <typename objType = void *>
  void triggerEvent(int eventType, objType data = nullptr);

  /**
   * Get the top event from the event queue   
   * @param event a reference to the pointer to an Event to store the obtained event
   * @return bool whether an event was returned successfully
   */
  bool pollEvent(Event *&event);

private:
  /**
   * Processess the events present in the default queue and move them to the custom queue   
   * @return void
   */
  void processEvents();
};

#include "RWindow.inl"

#endif