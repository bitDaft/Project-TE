/*
 * File: Game.hpp
 * Project: Project-TE
 * Created Date: Sunday June 9th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday December 27th 2019 10:41:38 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <map>

#include <SFML/Graphics.hpp>

#include "InputHandler.hpp"
#include "InputManager.hpp"
#include "ActionMapper.hpp"
#include "RWindow.hpp"
#include "UpdateManager.hpp"
#include "DrawManager.hpp"

/** 
 * An instance of the game
 * ^ The game class will have to be inherited to create a new actual game
 * ^ Currently it does not behave as such and the logic is written directly in the class files
*/
class Game : public InputHandler, private sf::NonCopyable
{
public:
    // Setup the game "engine" dependant stuff like the window and its options

    ~Game();
    Game();
    Game(const int wndWidth, const int wndHeight, const char *wndName);

    // Utility fuctions

    /**
     * Sets the size of the window 
     * @param width the new width of the window
     * @param height the new height of the window
     * @return void
     */
    void setWindowSize(const int width, const int height);
    /**
     * Sets the title of the window 
     * @param title the new title of the window
     * @return void
     */
    void setWindowTitle(const char *title);
    /**
     * Sets the framerate of the game loop 
     * @param seconds the new frame rate in seconds
     * @return void
     */
    void setFrameRate(const float seconds);
    /**
     * Gets the current frame rate 
     * @param 
     * @return void
     */
    double getFPS();

    /**
     * Starts the game loop 
     * @param 
     * @return void
     */
    void run();

    /**
     * Helper functions which can be bound to an input or called from inheriting class to close the game
     * @param sf::Event & The event that occured || void
     * @return bool whether to continue the daisy chain or stop
     */
    bool quit(sf::Event &);
    void quitForce();

    void startUpdation();
    void stopUpdation();
    void startDrawing();
    void stopDrawing();
    void startUpdationQueue(int);
    void stopUpdationQueue(int);
    void startDrawingQueue(int);
    void stopDrawingQueue(int);

private:
    /** 
     * An init function that is overriden which is executed once at the start of the game
     * Used to setup resources and other configuration
     * @return void
     */
    virtual void init();
    /** 
     * An overriden draw function that is called to allow for drawing of entities
     * @param sf::RenderWindow & A reference to the window onto which it should be drawn
     * @return void
     */
    // virtual void draw(const sf::Time &) = 0;
    /**
     * The event handler of the game loop 
     * @param 
     * @return void
     */
    void processEvents();
    /**
     * The custom event handler of the game loop 
     * @param Event & The Custom Event object reference
     * @return void
     */
    virtual void processCustomEvents(Event &);
    /**
     * The update funtion of the game loop which is overriden called for updating the game
     * @param sf::Time The step time need to update the game state by
     * @return void
     */
    // virtual void update(const sf::Time &) = 0;
    /**
     * Called after exit from the Game loop
     * @param 
     * @return void
     */
    virtual void end();
    /**
     * The display function of the game 
     * @param sf::Time The remaining delta time to render an interpolated state
     * @return void
     */
    void render(const sf::Time &);

    void commonInit();

private:
    sf::Time timePerFrame;
    bool initialized;
    bool isRunning;
    bool runUpdate;
    bool runDraw;
    double fps;
    UpdateManager *_updateManager; // ?is pointer needed
    DrawManager *_drawManager;     // ?is pointer needed

protected:
    RWindow gameWindow;
    ActionMapper _aMapper;
    InputManager _inputManager;
};

#endif