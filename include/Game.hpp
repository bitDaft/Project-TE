#pragma once

#include <SFML/Graphics.hpp>

class Game : private sf::NonCopyable
{
public:
    // * setup the game engine dependant stuff like the window and its options 
    Game();
    Game(int wndWidth, int wndHeight, char *wndName); 
    
    // * initializes the game to a known base state
    void init();
    void run();

private:
    void processEvents();
    void update(sf::Time);
    void render();

private:
    sf::RenderWindow gameWindow;
    const sf::Time timePerFrame;
    bool isRunning;
};