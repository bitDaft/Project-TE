#pragma once

#include <SFML/Graphics.hpp>
/** 
 * An instance of the game
 * ^ The game class will have to be inherited to create a new actual game
 * ^ Currently it does not behave as such and the logic is written directly in the class files
*/
class Game : private sf::NonCopyable
{
public:
    // Setup the game "engine" dependant stuff like the window and its options

    Game();
    Game(int wndWidth, int wndHeight, char *wndName);

    // Utility fuctions

    /**
     * Sets the size of the window 
     * @param width the new width of the window
     * @param height the new height of the window
     * @return void
     */
    void setWindowSize(int width, int height);
    /**
     * Sets the title of the window 
     * @param title the new title of the window
     * @return void
     */
    void setWindowTitle(char *title);
    /**
     * Sets the framerate of the game loop 
     * @param seconds the new frame rate in seconds
     * @return void
     */
    void setFrameRate(float seconds);

    /**
     * Starts the game loop 
     * @param 
     * @return void
     */
    void run();

    /** 
     * Initializes the game to a known base state
     * ? Shouldn't this function also be made overridable
     */
    void init();

private:
    // todo: These functions to be made virtual so as to be overridden
    // ^Not needed as of now as the game logic is directly written in the class

    /**
     * The event handler of the game loop 
     * @param 
     * @return void
     */
    void processEvents();
    /**
     * The update funtion of the game loop 
     * @param sf::Time The step time need to update the game state by
     * @return void
     */
    void update(sf::Time);
    /**
     * The display function of the game 
     * @param sf::Time The remaining delta time to render an interpolated state
     * @return void
     */
    void render(sf::Time);

private:
    sf::RenderWindow gameWindow;
    sf::Time timePerFrame;
    bool isRunning;
};