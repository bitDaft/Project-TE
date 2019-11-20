/*
 * File: UpdateManager.cpp
 * Project: Project-TE
 * Created Date: Tuesday November 19th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday November 20th 2019 2:37:19 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "UpdateManager.hpp"
#include <iostream>
#include <assert.h>

UpdateManager::UpdateManager()
{
  queueCount = 0;
  setupDone = false;
}
UpdateManager::~UpdateManager()
{
  queueCount = 0;
  updateCheck.clear();
  updateList.clear();
}

void UpdateManager::addQueue(int n)
{
  for (int i = 0; i < n; i++)
  {
    std::vector<IUpdatable *> t;
    updateList.push_back(t);
    updateCheck.push_back(true);
  }
}

void UpdateManager::intialise()
{
  setupDone = true;
}

void UpdateManager::pushToQueue(int pos, IUpdatable *ptr)
{
  assert(pos - 1 > 0);
  if (queueCount < pos)
  {
    std::cout << pos;
    addQueue(pos - queueCount);
    queueCount = pos;
  }
  updateList.at(pos - 1).push_back(ptr);
}

void UpdateManager::update(const sf::Time &t)
{
  if (setupDone)
  {
    for (int i = 0; i < queueCount; i++)
    {
      if (updateCheck[i])
      {
        for (std::vector<IUpdatable *>::iterator iit = updateList[i].begin(); iit != updateList[i].end(); ++iit)
        {
          (*iit)->callUpdate(t);
        }
      }
    }
  }
}
void UpdateManager::stopQueue(int pos)
{
  if (setupDone)
  {
    updateCheck.at(pos) = false;
  }
}
void UpdateManager::resumeQueue(int pos)
{
  if (setupDone)
  {
    updateCheck.at(pos) = true;
  }
}