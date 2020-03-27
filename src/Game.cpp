/*
 * File: Game.cpp
 * Project: Project-TE
 * Created Date: Sunday, March 22nd 2020, 7:30:00 pm
 * Author: bitDaft
 * -----
 * Last Modified: Friday, March 27th 2020 8:11:34 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2020 bitDaft
 */

#include <iostream>

#include "Game.hpp"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#define DEFAULT_FRAME_RATE (1.f / 120.f)
#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480
#define DEFAULT_GAME_NAME ("Project-TE")

// Default constructor

Game::~Game()
{
}
Game::Game()
    : timePerFrame(sf::seconds(DEFAULT_FRAME_RATE)),
      initialized(false),
      isRunning(true),
      runUpdate(false),
      runDraw(false),
      fps(0),
      _updateManager(new UpdateManager()),
      _drawManager(new DrawManager()),
      gameWindow(sf::VideoMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT), DEFAULT_GAME_NAME),
      _aMapper()
{
    commonInit();
}
// Constructor
Game::Game(const int w, const int h, const char *n)
    : timePerFrame(sf::seconds(DEFAULT_FRAME_RATE)),
      initialized(false),
      isRunning(true),
      runUpdate(false),
      runDraw(false),
      fps(0),
      _updateManager(new UpdateManager()),
      _drawManager(new DrawManager()),
      gameWindow(sf::VideoMode(w, h), n),
      _aMapper()
{
    commonInit();
}
void Game::commonInit()
{
    InputManager _inputManager(this);
    InputManager::setActionMapper(&_aMapper);
    
    gameWindow.setKeyRepeatEnabled(false);
    startUpdation();
    startDrawing();
    IUpdatable::initialize(_updateManager); 
    IDrawable::initialize(_drawManager);
}

void Game::setWindowSize(const int width, const int height)
{
    if (!initialized)
    {
        sf::Vector2u size;
        size.x = width;
        size.y = height;
        gameWindow.setSize(size);
    }
}

void Game::setWindowTitle(const char *title)
{
    if (!initialized)
    {
        gameWindow.setTitle(title);
    }
}

void Game::setFrameRate(const float seconds)
{
    if (!initialized)
    {
        timePerFrame = sf::seconds(1.f / seconds);
    }
}

void Game::run()
{
    initialized = true;
    finalTexture.create(gameWindow.getSize().x, gameWindow.getSize().y); 
    init();
    _updateManager->initialize();
    _drawManager->initialize();
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    // TODO: Re-evaluate loop
    // TODO: Panic check
    // TODO: interpolation
    int looper = 0;
    sf::Time time = sf::Time::Zero;
    while (isRunning)
    {
        processEvents();
        sf::Time dt = clock.restart();
        // ^simple panic check which caps the difference to 1 second
        // ^refactor it to actually handle a panic to revert to a determinable state instead of clamping
        // ^need to test the effect of clamping vs panic handling
        if (dt.asSeconds() > 1.f)
        {
            dt = sf::seconds(1.f);
        }

        // ^FPS handler
        if (time.asSeconds() > 1.f)
        {
            fps = 0.25 * looper + 0.75 * fps;
            looper = 0;
            time -= sf::seconds(1.f);
        }
        looper++;
        time += dt;
        timeSinceLastUpdate += dt;
        while ((timeSinceLastUpdate > timePerFrame) && isRunning)
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            if (runUpdate)
            {
                _updateManager->update(timePerFrame);
            }
        }
        // TODO: calculate the interpolation from the remaning time and pass it onto render so as to obtain the intermediary state
        // ?Instead of sending remaning time, why not send an interpolation ratio between [0,1]
        // sf::Time remaining_time = sf::Time::Zero; // !replace with the calculated time
        sf::Time remaining_time = timePerFrame; // !replace with the calculated time
        if (isRunning && runDraw)
        {
            render(remaining_time);
        }
    }
    end();
}
void Game::init() {}
void Game::end() {}
void Game::processEvents()
{
    Event *event;
    int eventsPerLoop = 25;
    while (gameWindow.pollEvent(event) && (eventsPerLoop-- > 0))
    {
        switch (event->type)
        {
        case sf::Event::Closed:
            isRunning = false;
            gameWindow.close();
            break;
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseMoved:
        case sf::Event::MouseWheelScrolled:
        case sf::Event::MouseWheelMoved:
        {
            sf::Event e;
            if (!event->getData(e))
            {
                break;
            }
            InputManager::processInputsEvent(e);
            break;
        }
        default:
            processCustomEvents(*event);
            break;
        }
        event->clear();
    }
}
void Game::processCustomEvents(Event &)
{
}
bool Game::quit(sf::Event &)
{
    isRunning = false;
    gameWindow.close();
    return false;
}
void Game::quitForce()
{
    isRunning = false;
    gameWindow.close();
}

void Game::render(const sf::Time &dt)
{
    // ?there will be calculation here to determine the intermediary positions
    // lets worry about shader to this texture later
    // although there is a way for it now
    gameWindow.clear();
    finalTexture.clear();
    _drawManager->draw(dt, finalTexture);
    finalTexture.display();
    gameWindow.draw(sf::Sprite(finalTexture.getTexture()));
    gameWindow.display();
}
double Game::getFPS()
{
    return fps;
}
void Game::startUpdation()
{
    runUpdate = true;
}
void Game::stopUpdation()
{
    runUpdate = false;
}
void Game::startDrawing()
{
    runDraw = true;
}
void Game::stopDrawing()
{
    runDraw = false;
}
void Game::stopUpdationQueue(int queue)
{
    _updateManager->stopQueue(queue);
}
void Game::startUpdationQueue(int queue)
{
    _updateManager->resumeQueue(queue);
}
void Game::stopDrawingQueue(int queue)
{
    _drawManager->stopQueue(queue);
}
void Game::startDrawingQueue(int queue)
{
    _drawManager->resumeQueue(queue);
}