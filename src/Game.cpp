/*
 * File: Game.cpp
 * Project: Project-TE
 * Created Date: Sunday June 9th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 3:13:02 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include "Game.hpp"
#include <iostream>

#define DEFAULT_FRAME_RATE (1.f / 120.f)
#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480
#define DEFAULT_GAME_NAME ("Application 1")

bool Game::quit(sf::RenderWindow &, sf::Event &)
{
    isRunning = false;
    gameWindow.close();
    return false;
}
bool Game::moveu(sf::RenderWindow &, sf::Event &)
{
    player.move({0.f, -1.f});
    return false;
}
bool Game::moved(sf::RenderWindow &, sf::Event &)
{
    player.move({0.f, 1.f});
    return false;
}
bool Game::movel(sf::RenderWindow &, sf::Event &)
{
    player.move({-1.f, 0.f});
    return false;
}
bool Game::mover(sf::RenderWindow &, sf::Event &)
{
    player.move({1.f, 0.f});
    return false;
}
// Default constructor
Game::Game()
    : gameWindow(sf::VideoMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT), DEFAULT_GAME_NAME),
      timePerFrame(sf::seconds(DEFAULT_FRAME_RATE)),
      isRunning(true), player(), textureManager(), handles(), _inputManager(this), _aMapper(), _rMapper(gameWindow, this)
{
    _reactionMapper = &_rMapper;
    gameWindow.setKeyRepeatEnabled(false);
    _inputManager.setActionMapper(&_aMapper);
}
// Constructor
Game::Game(const int w, const int h, const char *n)
    : gameWindow(sf::VideoMode(w, h), n),
      timePerFrame(sf::seconds(DEFAULT_FRAME_RATE)),
      isRunning(true), player(), textureManager(), handles(), _inputManager(this), _aMapper(), _rMapper(gameWindow, this)
{
    _reactionMapper = &_rMapper;
    gameWindow.setKeyRepeatEnabled(false);
    _inputManager.setActionMapper(&_aMapper);
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
        case sf::Event::KeyReleased:
            // case sf::Event::MouseButtonPressed:
            // case sf::Event::MouseButtonReleased:
            // case sf::Event::MouseMoved:
            // case sf::Event::MouseWheelScrolled:
            // case sf::Event::MouseWheelMoved:
            _inputManager.processInputsEvent(event);
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
    _aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyPressed, 1);
    _aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyReleased, 6);
    _aMapper.bindInputToAction(sf::Keyboard::Up, sf::Event::KeyPressed, 2);
    _aMapper.bindInputToAction(sf::Keyboard::Left, sf::Event::KeyPressed, 3);
    _aMapper.bindInputToAction(sf::Keyboard::Right, sf::Event::KeyPressed, 4);
    _aMapper.bindInputToAction(sf::Keyboard::Escape, sf::Event::KeyPressed, 5);
    // TODO: move evetn type to bining section for multiple binds
    _reactionMapper->bindActionToReaction<moved>(1);
    _reactionMapper->bindActionToReaction<mover>(6);
    _reactionMapper->bindActionToReaction<moveu>(2);
    _reactionMapper->bindActionToReaction<movel>(3);
    _reactionMapper->bindActionToReaction<mover>(4);
    _reactionMapper->bindActionToReaction<quit>(5);
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
