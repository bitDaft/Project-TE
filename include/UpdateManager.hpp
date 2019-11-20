/*
 * File: UpdateManager.hpp
 * Project: Project-TE
 * Created Date: Tuesday November 19th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday November 20th 2019 2:31:04 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef UPDATEMANAGER_HPP
#define UPDATEMANAGER_HPP

#include <vector>
#include <iostream>
#include <SFML/System/Time.hpp>
#include "IUpdatable.hpp"
#include "Game.hpp"

class UpdateManager
{
public:
  UpdateManager();
  virtual ~UpdateManager();

  void intialise();
  void pushToQueue(int, IUpdatable *);
  void update(const sf::Time &);
  void stopQueue(int = 0);
  void resumeQueue(int = 0);

private:
  void addQueue(int);

private:
  // contains variables detailing which queues are updatable
  // this is so multiple bytes may be reserved which will act as boolean for whether list can be iterated upon
  std::vector<bool> updateCheck;
  int queueCount;
  bool setupDone;
  // here there is a list of queues.. maybe a vector
  std::vector<std::vector<IUpdatable *>> updateList;
};

#endif