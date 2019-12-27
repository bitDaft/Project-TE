/*
 * File: UpdateManager.hpp
 * Project: Project-TE
 * Created Date: Tuesday November 19th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:41:38 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef UPDATEMANAGER_HPP
#define UPDATEMANAGER_HPP

#include <vector>

#include <SFML/System/Time.hpp>

#include "IUpdatable.hpp"

// ?effiicient use of vector
// ?quick way to store lots of object and reference them
// ?remember how minecraft stores their chunks in bins with hashing
// ?maybe use something similar to it to find quickly and retrieve it

/** 
 * This class manages the updation queue and updation of all the objects added to the queue
 * ^ Manual initialization of this class is not needed as only one object of this class is needed
 * ^ That object is created and managed by the Game class
 * ^ Any functionality that needs to be given to updatables can be opened through the IUpdatable interface
 * TODO allow changing of queues of objects
*/
class UpdateManager
{
public:
  // constructor destructor
  UpdateManager();
  virtual ~UpdateManager();

  /**
   * Initializes the object to start the updation pipeline  
   * @return void
   */
  void initialize();

  /**
   * This runs through all the object queues and updates them  
   * @param dt the remaining delta time needed to calculate an interpolated state
   * @return void
   */
  void update(const sf::Time &dt);

  /**
   * Prevents an object queue from updating its objects  
   * @param queuePos the position of the queue which should not be updated
   * @return void
   */
  void stopQueue(int queuePos);

  /**
   * Allows an object queue from updating its objects  
   * @param queuePos the position of the queue which should be allowed to be updated
   * @return void
   */
  void resumeQueue(int queuePos);

  /**
   * Pushes a pointer of an IUpdatable object into an object queue  
   * @param queuePos the queue into which the IUpdatable pointer is to be pushed into 
   * @param updatable the IUpdatable that is be added to the updation queue
   * @return void
   */
  int pushToQueue(int queuePos, IUpdatable *updatable);

  /**
   * Removes a pointer of an IUpdatable object from an object queue  
   * @param queuePos the queue from which the IUpdatable pointer is to be removed 
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
   * Cleans up all deleted and removed objects from the updation queue to free up space  
   * @return void
   */
  void cleanupQueue();

private:
  std::vector<bool> updateCheck;
  int queueCount;
  bool setupDone;
  std::vector<std::vector<IUpdatable *>> updateList;
};

#endif