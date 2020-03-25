/*
 * File: DrawManager.cpp
 * Project: Project-TE
 * Created Date: Sunday December 1st 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday, March 24th 2020 4:24:36 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2019 bitDaft
 */

#include <iostream>
#include <algorithm>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "DrawManager.hpp"

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

void DrawManager::addQueue(int count)
{
  drawCheck.reserve(queueCount + count);
  drawList.reserve(queueCount + count);
  for (int i = 0; i < count; i++)
  {
    std::vector<IDrawable *> t;
    drawList.emplace_back(t);
    drawList.at(drawList.size() - 1).reserve(50);
    drawCheck.push_back(true);
  }
}

void DrawManager::initialize()
{
  setupDone = true;
}

int DrawManager::pushToQueue(int queuePos, IDrawable *drawable)
{
  if (queueCount < queuePos)
  {
    addQueue(queuePos - queueCount);
    queueCount = queuePos;
  }
  drawList.at(queuePos - 1).emplace_back(drawable);
  return drawList.at(queuePos - 1).size() - 1;
}
void DrawManager::removeFromQueue(int queuePos, int objectPos)
{
  drawList.at(queuePos).at(objectPos) = nullptr;
}
void DrawManager::draw(const sf::Time &dt, sf::RenderTexture &finalTexture)
{
  if (setupDone)
  {
    sf::RenderTexture _tex;
    
    _tex.create(finalTexture.getSize().x, finalTexture.getSize().y);
    for (int i = 0; i < queueCount; i++) // ?make it std::size_t
    {
      if (drawCheck.at(i))
      {
        std::size_t failCount = 0;
        _tex.clear(sf::Color::Transparent);
        for (std::size_t j = 0; j < drawList[i].size(); ++j)
        {
          if (drawList[i].at(j))
          {
            if (drawList[i][j]->canDraw)
            {
              drawList[i][j]->draw(dt, _tex);
            }
          }
          else
          {
            failCount++;
          }
        }

        // ? maybe instead of just following painters algoritm see whther we can create a mask from the already created texture so that the new 
        // ? texture that is going to blitted is not gonna draw useless parts of it which is hidden in a higher layer

        // what we want is to not have it drawn but obtain the vertices
        // so that we can draw the vertices for the same texture
        // currently this is slow and inefficient will have to change later
        // group vertices by texture and and then loop through it and do multiple draw calls.
        // it will be better if all were stored on the same texture file.
        // let us see how this turns out later

        _tex.display();

        // pass each queue image to the shader pipeline
        // get the shader from user to be passed from somehwere
        // add this image to the final image
        // shader sh = getshader(i);
        // if(sh){
        // finalTexture.draw(sf::Sprite(_tex.getTexture()),sh);
        // }else{
        finalTexture.draw(sf::Sprite(_tex.getTexture()));
        // }

        if (failCount > 10 && failCount >= (drawList[i].size() >> 2))
        {
          cleanupQueue(i);
        }
      }
    }
    // pass the final image to the shader pipeline
  }
}

void DrawManager::cleanupQueue(int pos)
{
  drawList[pos].erase(
      std::remove_if(
          drawList[pos].begin(),
          drawList[pos].end(),
          [](IDrawable *ptr) { return ptr == nullptr; }),
      drawList[pos].end());

  for (std::size_t i = 0; i < drawList[pos].size(); ++i)
  {
    drawList[pos][i]->_2 = i;
  }
}
void DrawManager::stopQueue(int queuePos)
{
  if (setupDone)
  {
    drawCheck.at(queuePos - 1) = false;
  }
}
void DrawManager::resumeQueue(int queuePos)
{
  if (setupDone)
  {
    drawCheck.at(queuePos - 1) = true;
  }
}