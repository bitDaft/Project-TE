/*
 * File: UpdateManager.hpp
 * Project: Project-TE
 * Created Date: Tuesday November 19th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday November 21st 2019 10:58:25 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef DRAWMANAGER_HPP
#define DRAWMANAGER_HPP

#include <vector>
#include <SFML/System/Time.hpp>
#include "IDrawable.hpp"


// effiicient use of vector
// quick way to store lots of object and reference them
// remember how minecraft stores their chunks in bins with hashing
// maybe use something similar to it to find quickly and retrieve it

class DrawManager
{
public:
  DrawManager();
  virtual ~DrawManager();

  void intialise();
  void draw(const sf::Time &);
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