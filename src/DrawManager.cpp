/*
 * File: DrawManager.cpp
 * Project: Project-TE
 * Created Date: Sunday December 1st 2019
 * Author: bitDaft
 * -----
 * Last Modified: Sunday December 1st 2019 11:48:23 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include "DrawManager.hpp"
#include <iostream>
#include <algorithm>

DrawManager::DrawManager()
{
  queueCount = 0;
  setupDone = false;
  drawList.reserve(5);
  drawCheck.reserve(5);
}
DrawManager::~DrawManager()
{
  queueCount = 0;
  drawCheck.clear();
  drawList.clear();
}

void DrawManager::addQueue(int n)
{
  drawCheck.reserve(queueCount + n);
  drawList.reserve(queueCount + n);
  for (int i = 0; i < n; i++)
  {
    std::vector<IDrawable *> t;
    drawList.emplace_back(t);
    drawList.at(drawList.size() - 1).reserve(50);
    drawCheck.push_back(true);
  }
}

void DrawManager::intialise()
{
  setupDone = true;
}

int DrawManager::pushToQueue(int pos, IDrawable *ptr)
{
  if (queueCount < pos)
  {
    addQueue(pos - queueCount);
    queueCount = pos;
  }
  drawList.at(pos - 1).emplace_back(ptr);
  return drawList.at(pos - 1).size() - 1;
}
void DrawManager::removeFromQueue(int pos1, int pos2)
{
  drawList.at(pos1).at(pos2) = nullptr;
}
void DrawManager::draw(const sf::Time &t)
{
  if (setupDone)
  {
    int failCount = 0;
    int totalCount = 0;
    for (int i = 0; i < queueCount; i++)
    {
      if (drawCheck[i])
      {
        totalCount += drawList.at(i).size();
        for (std::size_t j = 0; j < drawList[i].size(); ++j)
        {
          if (drawList[i].at(j))
          {
            drawList[i][j]->callDraw(t);
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

void DrawManager::cleanupQueue()
{
  for (int i = 0; i < queueCount; i++)
  {
    drawList[i].erase(
        std::remove_if(
            drawList[i].begin(),
            drawList[i].end(),
            [](IDrawable *ptr) { return ptr == nullptr; }),
        drawList[i].end());
  }
}
void DrawManager::stopQueue(int pos)
{
  if (setupDone)
  {
    drawCheck.at(pos - 1) = false;
  }
}
void DrawManager::resumeQueue(int pos)
{
  if (setupDone)
  {
    drawCheck.at(pos - 1) = true;
  }
}