/*
 * File: IDrawable.hpp
 * Project: Project-TE
 * Created Date: Sunday December 1st 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:41:38 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

class DrawManager;

/** 
 * An interface for drawable objects
 * ^ This class will have to be inherited to be able to be drawn onto the screen using the drawing pipeline
 * ^ It will allow enable and disable drawing of objects and pushing them onto drawing queue
 * ^ no additional functionality for priority is given within a queue
 * ^ all objects added to the queue is appended to the end of the queue
 * ^ if needed to change the priority just add a new queue
 * ^ currently does not possess functionality to change queues
 * TODO changing of queues need to be implemented 
*/
class IDrawable
{
public:
  // constructor destructor
  IDrawable(int pos);
  virtual ~IDrawable();

  /**
   * Called by the DrawManager object to call the actual draw function  
   * ^ should change later to make it return the texture and the vertices instead of drawing to reduce the draw calls 
   * @param dt the remaining delta time needed to calculate an interpolated state
   * @param renderTexture a renderable texture to which the objects should be drawn to
   * @return void
   */
  void callDraw(const sf::Time &dt, sf::RenderTexture &renderTexture);

  /**
   * Sets the global DrawManager object used for drawing management  
   * manager can only be set once, this is set by the game class itself
   * @param drawManager pointer to the global DrawManager object
   * @return void
   */
  static void initialize(DrawManager *drawManager);

protected:
  // utility function

  /**
   * allow this object to be drawn   
   * @return void
   */
  void enableDraw();

  /**
   * prevent this object from being drawn   
   * @return void
   */
  void disableDraw();

private:
  /**
   * Should be overriden by inheriting functions to draw themselves onto the RenderTexture 
   * ^ should change later to make it return the texture and the vertices instead of drawing to reduce the draw calls 
   * @param dt the remaining delta time needed to calculate an interpolated state
   * @param renderTexture a renderable texture to which the objects should be drawn to
   * @return void
   */
  virtual void draw(const sf::Time &dt, sf::RenderTexture &renderTexture) = 0;

private:
  int _1;
  int _2;
  bool canDraw;
  static DrawManager *_u;
};

#endif