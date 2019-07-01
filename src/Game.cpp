/*
 * File: Game.cpp
 * Project: Project-TE
 * Created Date: Sunday June 9th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Friday June 28th 2019 12:05:43 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Game.hpp"

#define DEFAULT_FRAME_RATE (1.f / 120.f)
#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480
#define DEFAULT_GAME_NAME ("Application 1")

// Default constructor
Game::Game()
    : gameWindow(sf::VideoMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT), DEFAULT_GAME_NAME),
      timePerFrame(sf::seconds(DEFAULT_FRAME_RATE)),
      isRunning(true), player(), textureManager(), handles()
{
    gameWindow.setKeyRepeatEnabled(false);
}
// Constructor
Game::Game(const int w, const int h, const char *n)
    : gameWindow(sf::VideoMode(w, h), n),
      timePerFrame(sf::seconds(DEFAULT_FRAME_RATE)),
      isRunning(true), player(), textureManager(), handles()
{
    gameWindow.setKeyRepeatEnabled(false);
}

void Game::setWindowSize(const int width, const int height)
{
    sf::Vector2u size;
    size.x = width;
    size.y = height;
    gameWindow.setSize(size);
}

void Game::setWindowTitle(const char *title)
{
    gameWindow.setTitle(title);
}

void Game::setFrameRate(const float seconds)
{
    timePerFrame = sf::seconds(1.f / seconds);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    init();
    // todo: Re-evaluate loop
    // todo: Panic check
    // todo: interpolation
    int looper = 0;
    float fps = 60;
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
            setWindowTitle(std::to_string(int(fps)).c_str());
            looper = 0;
            time -= sf::seconds(1.f);
        }
        looper++;
        time += dt;
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            update(timePerFrame);
        }
        // todo: calculate the interpolation from the remaning time and pass it onto render so as to obtain the intermediary state
        // ?Instead of sending remaning time, why not send an interpolation ration between [0,1]
        sf::Time remaining_time = sf::Time::Zero; // !replace with the calculated time
        render(remaining_time);
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
            if (event.key.code == sf::Keyboard::Escape)
            {
                isRunning = false;
                gameWindow.close();
            }

            break;
        case sf::Event::KeyReleased:
            break;

        default:
            break;
        }
    }
}

void Game::init()
{
    unsigned int playerTexture = textureManager.loadTexture("assets/player.png");
    handles.insert(std::make_pair(TEXTURE::PLAYER, playerTexture));
    player.setTexture(textureManager.getTexture(playerTexture));
}

void Game::update(const sf::Time dt)
{
}

void Game::render(const sf::Time dt)
{
    // there will be calculation here to determine the intermediary positions
    gameWindow.clear();
    gameWindow.draw(player);
    gameWindow.display();
}
