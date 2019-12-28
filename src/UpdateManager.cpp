/*
 * File: UpdateManager.cpp
 * Project: Project-TE
 * Created Date: Tuesday November 19th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Saturday December 28th 2019 11:48:14 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include <iostream>
#include <algorithm>

#include "UpdateManager.hpp"

UpdateManager::UpdateManager()
{
  queueCount = 0;
  setupDone = false;
  updateList.reserve(5);
  updateCheck.reserve(5);
}
UpdateManager::~UpdateManager()
{
  queueCount = 0;
  updateCheck.clear();
  updateList.clear();
}

void UpdateManager::addQueue(int count)
{
  updateCheck.reserve(queueCount + count);
  updateList.reserve(queueCount + count);
  for (int i = 0; i < count; i++)
  {
    std::vector<IUpdatable *> t;
    updateList.emplace_back(t);
    updateList.at(updateList.size() - 1).reserve(50);
    updateCheck.push_back(true);
  }
}

void UpdateManager::initialize()
{
  setupDone = true;
}

int UpdateManager::pushToQueue(int queuePos, IUpdatable *updatable)
{
  if (queueCount < queuePos)
  {
    addQueue(queuePos - queueCount);
    queueCount = queuePos;
  }
  updateList.at(queuePos - 1).emplace_back(updatable);
  return updateList.at(queuePos - 1).size() - 1;
}
void UpdateManager::removeFromQueue(int queuePos, int objectPos)
{
  updateList.at(queuePos).at(objectPos) = nullptr;
}
void UpdateManager::update(const sf::Time &dt)
{
  if (setupDone)
  {
    for (int i = 0; i < queueCount; i++)
    {
      if (updateCheck[i])
      {
        std::size_t failCount = 0;
        for (std::size_t j = 0; j < updateList[i].size(); ++j)
        {
          if (updateList[i].at(j))
          {
            if (updateList[i][j]->canUpdate)
            {
              updateList[i][j]->update(dt);
            }
          }
          else
          {
            failCount++;
          }
        }
        if (failCount > 10 && failCount >= (updateList.at(i).size() >> 1))
        {
          cleanupQueue(i);
        }
      }
    }
  }
}
void UpdateManager::cleanupQueue(int pos)
{

  updateList[pos].erase(
      std::remove_if(
          updateList[pos].begin(),
          updateList[pos].end(),
          [](IUpdatable *ptr) { return ptr == nullptr; }),
      updateList[pos].end());

  for (std::size_t i = 0; i < updateList[pos].size(); ++i)
  {
    updateList[pos][i]->_2 = i;
  }
}
void UpdateManager::stopQueue(int queuePos)
{
  if (setupDone)
  {
    updateCheck.at(queuePos - 1) = false;
  }
}
void UpdateManager::resumeQueue(int queuePos)
{
  if (setupDone)
  {
    updateCheck.at(queuePos - 1) = true;
  }
}