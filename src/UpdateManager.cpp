/*
 * File: UpdateManager.cpp
 * Project: Project-TE
 * Created Date: Tuesday November 19th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday November 22nd 2019 10:17:01 am
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

void UpdateManager::addQueue(int n)
{
  for (int i = 0; i < n; i++)
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

int UpdateManager::pushToQueue(int pos, IUpdatable *ptr)
{
  if (queueCount < pos)
  {
    addQueue(pos - queueCount);
    queueCount = pos;
  }
  updateList.at(pos - 1).emplace_back(ptr);
  return updateList.at(pos - 1).size() - 1;
}
void UpdateManager::removeFromQueue(int pos1, int pos2)
{
  updateList.at(pos1).at(pos2) = nullptr;
}
void UpdateManager::update(const sf::Time &t)
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
            updateList[i][j]->callUpdate(t);
          }
          else
          {
            failCount++;
          }
        }
      }
    }
    if (failCount > 10 && failCount >= (totalCount >> 2))
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
void UpdateManager::stopQueue(int pos)
{
  if (setupDone)
  {
    updateCheck.at(pos - 1) = false;
  }
}
void UpdateManager::resumeQueue(int pos)
{
  if (setupDone)
  {
    updateCheck.at(pos - 1) = true;
  }
}