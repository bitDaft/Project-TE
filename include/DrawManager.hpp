/*
 * File: DrawManager.hpp
 * Project: Project-TE
 * Created Date: Sunday December 1st 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday December 1st 2019 8:34:11 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef DRAWMANAGER_HPP
#define DRAWMANAGER_HPP

#include <vector>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "IDrawable.hpp"

class DrawManager
{
public:
  DrawManager();
  virtual ~DrawManager();

  void intialise();
  void draw(const sf::Time &,sf::RenderTexture &);
  void stopQueue(int);
  void resumeQueue(int);

  int pushToQueue(int, IDrawable *);
  void removeFromQueue(int, int);

private:
  void addQueue(int);
  void cleanupQueue();

private:
  std::vector<bool> drawCheck;
  int queueCount;
  bool setupDone;
  std::vector<std::vector<IDrawable *>> drawList;
};

#endif