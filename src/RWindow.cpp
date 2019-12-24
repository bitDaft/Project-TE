/*
 * File: RWindow.cpp
 * Project: Project-TE
 * Created Date: Thursday August 29th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday December 24th 2019 5:45:16 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "RWindow.hpp"

RWindow::RWindow()
{
}
RWindow::RWindow(sf::VideoMode v,
                 const sf::String &s,
                 sf::Uint32 style,
                 const sf::ContextSettings &settings)
    : RenderWindow(v, s, style, settings)
{
}
RWindow::RWindow(sf::WindowHandle handle, const sf::ContextSettings &settings)
    : RenderWindow(handle, settings)
{
}
RWindow::~RWindow()
{
}

bool RWindow::pollEvent(Event *&event)
{
  processEvents();
  return popEvent(event);
}

void RWindow::processEvents()
{
  sf::Event _n;
  while (sf::RenderWindow::pollEvent(_n))
  {
    sf::Event *se = new sf::Event(_n);
    pushEvent<sf::Event>(se->type, se);
  }
}
