/*
 * File: IUpdatable.hpp
 * Project: Project-TE
 * Created Date: Monday November 18th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:41:38 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef IUPDATABLE_HPP
#define IUPDATABLE_HPP

#include <SFML/System/Time.hpp>
class UpdateManager;

/** 
 * An interface for updatable objects
 * ^ This class will have to be inherited to be able to be updated
 * ^ no additional functionality for priority is given within a queue
 * ^ all objects added to the queue is appended to the end of the queue
 * ^ if needed to change the priority just add a new queue
 * ^ currently does not possess functionality to change queues
 * TODO changing of queues need to be implemented 
*/
class IUpdatable
{
public:
  // constructor destructor
  IUpdatable(int pos);
  virtual ~IUpdatable();

  /**
   * Called by the UpdateManager object to call the actual update function  
   * @param dt the elapsed time for the frame
   * @return void
   */
  void callUpdate(const sf::Time &dt);

  /**
   * Sets the global UpdateManager object used for update management  
   * manager can only be set once, this is set by the game class itself
   * @param updateManager pointer to the global UpdateManager object
   * @return void
   */
  static void initialize(UpdateManager *updateManager);

protected:
  // utility function

  /**
   * Allow this object to be updated   
   * @return void
   */
  void enableUpdate();

  /**
   * Prevent this object from being updated   
   * @return void
   */
  void disableUpdate();

private:
  /**
   * Should be overriden by inheriting functions to update themselves 
   * @param dt the elapsed time for the frame
   * @return void
   */
  virtual void update(const sf::Time &dt) = 0;

private:
  int _1;
  int _2;
  bool canUpdate;
  static UpdateManager *_u;
};

#endif