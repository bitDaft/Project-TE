/*
 * File: UpdateManager.cpp
 * Project: Project-TE
 * Created Date: Tuesday November 19th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Thursday November 21st 2019 10:58:25 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "UpdateManager.hpp"
#include <assert.h>
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
    t.reserve(50);
    updateList.emplace_back(t);
    updateCheck.push_back(true);
  }
}

void UpdateManager::intialise()
{
  setupDone = true;
}

int UpdateManager::pushToQueue(int pos, IUpdatable *ptr)
{
  assert(pos - 1 > 0);
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
        totalCount += updateList[i].size();
        for (std::vector<IUpdatable *>::iterator iit = updateList[i].begin(); iit != updateList[i].end(); ++iit)
        {
          if (iit != nullptr)
          {
            (*iit)->callUpdate(t);
          }
          else
          {
            failCount++;
          }
        }
      }
    }
    if (failCount >= (totalCount >> 2))
    {
      cleanupQueue();
    }
  }
}
void UpdateManager::cleanupQueue()
{
  std::cout << "called cleanup\n";
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