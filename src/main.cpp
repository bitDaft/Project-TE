/*
 * File: main.cpp
 * Project: Project-TE
 * Created Date: Sunday June 9th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 2:31:43 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include <iostream>
#include "Game.hpp"

enum Actions
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_RELEASE,
	DOWN_RELEASE,
	LEFT_RELEASE,
	RIGHT_RELEASE,
	QUIT
};

class TestPlayer : public Entity
{
private:
	sf::Sprite player;
	float playerMoveSpeed;

private:
	bool moveUpR(sf::Event &)
	{
		plVelocity.y += playerMoveSpeed;
		return false;
	}
	bool moveDownR(sf::Event &)
	{
		plVelocity.y -= playerMoveSpeed;
		return false;
	}
	bool moveLeftR(sf::Event &)
	{
		plVelocity.x += playerMoveSpeed;
		return false;
	}
	bool moveRightR(sf::Event &)
	{
		plVelocity.x -= playerMoveSpeed;
		return false;
	}
	bool moveUp(sf::Event &)
	{
		plVelocity.y -= playerMoveSpeed;
		return false;
	}
	bool moveDown(sf::Event &)
	{
		plVelocity.y += playerMoveSpeed;
		return false;
	}
	bool moveLeft(sf::Event &)
	{
		plVelocity.x -= playerMoveSpeed;
		return false;
	}
	bool moveRight(sf::Event &)
	{
		plVelocity.x += playerMoveSpeed;
		return false;
	}

public:
	sf::Vector2f plVelocity;
	~TestPlayer() { }
	TestPlayer(sf::RenderWindow &win) : Entity(this), plVelocity(0, 0), playerMoveSpeed(50.f)
	{
		player.setPosition(100.f, 100.f);
		_reactionMapper->bindActionToReaction<moveUpR>(Actions::UP_RELEASE);
		_reactionMapper->bindActionToReaction<moveDownR>(Actions::DOWN_RELEASE);
		_reactionMapper->bindActionToReaction<moveLeftR>(Actions::LEFT_RELEASE);
		_reactionMapper->bindActionToReaction<moveRightR>(Actions::RIGHT_RELEASE);
		_reactionMapper->bindActionToReaction<moveDown>(Actions::DOWN);
		_reactionMapper->bindActionToReaction<moveUp>(Actions::UP);
		_reactionMapper->bindActionToReaction<moveLeft>(Actions::LEFT);
		_reactionMapper->bindActionToReaction<moveRight>(Actions::RIGHT);
	}
	void settexture(sf::Texture &tex)
	{
		player.setTexture(tex);
	}
	const sf::Vector2f getPosition()
	{
		return player.getPosition();
	}
	void move(const sf::Vector2f &t)
	{
		player.move(t);
	}
	const sf::Sprite &getSprite()
	{
		return player;
	}
};

class Test : public Game
{
private:
	TestPlayer pl;

public:
	Test(const int wndWidth, const int wndHeight, const char *wndName) : Game(wndWidth, wndHeight, wndName), pl(gameWindow)
	{
	}

	void init()
	{
		const unsigned int playerHandle = textureManager.loadTexture("assets/player.png");
		pl.settexture(textureManager.getTexture(playerHandle));
		_aMapper.bindInputToAction(sf::Keyboard::Up, sf::Event::KeyPressed, Actions::UP);
		_aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyPressed, Actions::DOWN);
		_aMapper.bindInputToAction(sf::Keyboard::Left, sf::Event::KeyPressed, Actions::LEFT);
		_aMapper.bindInputToAction(sf::Keyboard::Right, sf::Event::KeyPressed, Actions::RIGHT);
		_aMapper.bindInputToAction(sf::Keyboard::Up, sf::Event::KeyReleased, Actions::UP_RELEASE);
		_aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyReleased, Actions::DOWN_RELEASE);
		_aMapper.bindInputToAction(sf::Keyboard::Left, sf::Event::KeyReleased, Actions::LEFT_RELEASE);
		_aMapper.bindInputToAction(sf::Keyboard::Right, sf::Event::KeyReleased, Actions::RIGHT_RELEASE);
		_aMapper.bindInputToAction(sf::Keyboard::Escape, sf::Event::KeyPressed, Actions::QUIT);

		_inputManager.pushEntity(&pl);

		_reactionMapper->bindActionToReaction<quit>(Actions::QUIT);
	}
	void update(const sf::Time t)
	{
		if (pl.getPosition().x < 0 || pl.getPosition().x > 480)
			pl.plVelocity.x = -pl.plVelocity.x;
		if (pl.getPosition().y < 0 || pl.getPosition().y > 320)
			pl.plVelocity.y = -pl.plVelocity.y;
		pl.move(pl.plVelocity * t.asSeconds());
	}
	void draw(sf::RenderWindow &win)
	{
		win.draw(pl.getSprite());
	}
};

int main(int argc, char *argv[])
{
	Test testGame(480, 320, "Hello, World!");
	testGame.run();
	return 0;
}