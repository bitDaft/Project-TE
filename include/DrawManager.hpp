/*
 * File: DrawManager.hpp
 * Project: Project-TE
 * Created Date: Sunday December 1st 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:41:38 am
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

/** 
 * This class manages the drawing queue and drawing of all the objects added to the queue
 * ^ Manual initialization of this class is not needed as only one object of this class is needed
 * ^ That object is created and managed by the Game class
 * ^ Any functionality that needs to be given to drawables can be opened through the IDrawable interface
 * TODO allow changing of queues of objects
*/
class DrawManager
{
public:
  // constructor destructor
  DrawManager();
  virtual ~DrawManager();

  /**
   * Initializes the object to start the drawing pipeline  
   * @return void
   */
  void initialize();

  /**
   * This runs through all the object queues and draws them to the RenderTexture  
   * @param dt the remaining delta time needed to calculate an interpolated state
   * @param renderTexture a renderable texture to which the objects should be drawn to
   * @return void
   */
  void draw(const sf::Time &dt, sf::RenderTexture &renderTexture);

  /**
   * Prevents an object queue from drawing its objects  
   * @param queuePos the position of the queue which should not be drawn
   * @return void
   */
  void stopQueue(int queuePos);

  /**
   * Allows an object queue from drawing its objects  
   * @param queuePos the position of the queue which should be allowed to be drawn
   * @return void
   */
  void resumeQueue(int queuePos);

  /**
   * Pushes a pointer of an IDrawable object into an object queue  
   * @param queuePos the queue into which the IDrawable pointer is to be pushed into 
   * @param drawable the IDrawable that is be added to the drawing queue
   * @return void
   */
  int pushToQueue(int queuePos, IDrawable *drawable);

  /**
   * Removes a pointer of an IDrawable object from an object queue  
   * @param queuePos the queue from which the IDrawable pointer is to be removed 
   * @param objectPos the position of the object in the given queue
   * @return void
   */
  void removeFromQueue(int queuePos, int objectPos);

private:
  /**
   * Adds a new object queue  
   * @param count number of new queues to be added
   * @return void
   */
  void addQueue(int count);

  /**
   * Cleans up all deleted and removed objects from the drawing queue to free up space  
   * @return void
   */
  void cleanupQueue();

private:
  std::vector<bool> drawCheck;
  int queueCount;
  bool setupDone;
  std::vector<std::vector<IDrawable *>> drawList;
};

#endif