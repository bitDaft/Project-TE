#include "Game.hpp"

#define DEFAULT_FRAME_RATE (1.f / 120.f)
#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480
#define DEFAULT_GAME_NAME ("Application 1")

Game::Game() : gameWindow(sf::VideoMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT), DEFAULT_GAME_NAME),
               timePerFrame(sf::seconds(DEFAULT_FRAME_RATE)),
               isRunning(true)
{
}
Game::Game(int w, int h, char *n) : gameWindow(sf::VideoMode(w, h), n),
                                    timePerFrame(sf::seconds(DEFAULT_FRAME_RATE)),
                                    isRunning(true)
{
}
void Game::setWindowSize(int width,int height){
    sf::Vector2u size;
    size.x = width;
    size.y = height;
    gameWindow.setSize(size);
}
void Game::setWindowTitle(char *title){
    gameWindow.setTitle(title);
}
void Game::setFrameRate(float seconds)
{
    timePerFrame = sf::seconds(1.f/seconds);
}

// TODO : Re-evaluate loop
// TODO : Panic check
// TODO : interpolation
void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (isRunning)
    {
        processEvents();
        sf::Time dt = clock.restart();
        // * simple panic check which caps the difference to one second
        // * refactor it to actually handle a panic to revert to a determinable state instead of clamping
        // * need to test the effect of clamping vs panic handling
        if(dt.asSeconds() > 1.f)
        {
            dt = sf::seconds(1.f);
        }
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            update(timePerFrame);
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (gameWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            isRunning = false;
            gameWindow.close();
            break;
        case sf::Event::KeyPressed:
            isRunning = false;
            gameWindow.close();
            break;

        default:
            break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
}

void Game::render()
{
    gameWindow.clear();
    gameWindow.display();
}
