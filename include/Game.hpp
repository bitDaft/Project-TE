/*
 * File: Game.hpp
 * Project: Project-TE
 * Created Date: Sunday June 9th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 3:26:28 pm
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
#include "ResourceManager.hpp"

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
     * Starts the game loop 
     * @param 
     * @return void
     */
    void run();

    /**
     * A helper function which can be bound to an input to close the game
     * @param sf::Event & The event that occured
     * @return bool whether to continue the daisy chain or stop
     */
    bool quit(sf::Event &);

private:
    /** 
     * An init function that is overriden which is executed once at the start of the game
     * Used to setup resources and other configuration
     * @return void
     */
    virtual void init() = 0;
    /** 
     * An overriden draw function that is called to allow for drawing of entities
     * @param sf::RenderWindow & A reference to the window onto which it should be drawn
     * @return void
     */
    virtual void draw(sf::RenderWindow &) = 0;
    /**
     * The event handler of the game loop 
     * @param 
     * @return void
     */
    void processEvents();
    /**
     * The update funtion of the game loop which is overriden called for updating the game
     * @param sf::Time The step time need to update the game state by
     * @return void
     */
    virtual void update(const sf::Time) = 0;
    /**
     * The display function of the game 
     * @param sf::Time The remaining delta time to render an interpolated state
     * @return void
     */
    void render(const sf::Time);

private:
    sf::Time timePerFrame;
    bool isRunning;

protected:
    sf::RenderWindow gameWindow;
    ActionMapper _aMapper;
    InputManager _inputManager;
};

#endif