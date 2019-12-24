/*
 * File: UpdateManager.cpp
 * Project: Project-TE
 * Created Date: Tuesday November 19th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday December 24th 2019 5:16:49 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "UpdateManager.hpp"
#include <iostream>
#include <algorithm>

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

void UpdateManager::intialise()
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
    int failCount = 0;
    int totalCount = 0;
    for (int i = 0; i < queueCount; i++)
    {
      if (updateCheck[i])
      {
        totalCount += updateList.at(i).size();
        for (std::size_t j = 0; j < updateList[i].size(); ++j)
        {
          if (updateList[i].at(j))
          {
            updateList[i][j]->callUpdate(dt);
          }
          else
          {
            failCount++;
          }
        }
      }
    }
    if (failCount > 10 && failCount >= (totalCount >> 1))
    {
      cleanupQueue();
    }
  }
}
void UpdateManager::cleanupQueue()
{
  for (int i = 0; i < queueCount; i++)
  {
    updateList[i].erase(
        std::remove_if(
            updateList[i].begin(),
            updateList[i].end(),
            [](IUpdatable *ptr) { return ptr == nullptr; }),
        updateList[i].end());
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