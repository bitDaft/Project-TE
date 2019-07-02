/*
 * File: main.cpp
 * Project: Project-TE
 * Created Date: Sunday June 9th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday July 2nd 2019 5:06:52 pm
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
	QUIT
};

class Test : public Game
{
private:
	sf::Sprite player;
	sf::Vector2f plVelocity;
	float playerMoveSpeed;

public:
	Test(const int wndWidth, const int wndHeight, const char *wndName) : Game(wndWidth, wndHeight, wndName), plVelocity(0, 0), playerMoveSpeed(30.f)
	{
	}
	bool moveUp(sf::RenderWindow &, sf::Event &)
	{
		plVelocity.y -= playerMoveSpeed;
		return false;
	}
	bool moveDown(sf::RenderWindow &, sf::Event &)
	{
		plVelocity.y += playerMoveSpeed;
		return false;
	}
	bool moveLeft(sf::RenderWindow &, sf::Event &)
	{
		plVelocity.x -= playerMoveSpeed;
		return false;
	}
	bool moveRight(sf::RenderWindow &, sf::Event &)
	{
		plVelocity.x += playerMoveSpeed;
		return false;
	}
	void init()
	{
		const unsigned int playerHandle = textureManager.loadTexture("assets/player.png");
		player.setTexture(textureManager.getTexture(playerHandle));
		player.setPosition(100.f, 100.f);
		_aMapper.bindInputToAction(sf::Keyboard::Up, sf::Event::KeyPressed, Actions::UP);
		_aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyPressed, Actions::DOWN);
		_aMapper.bindInputToAction(sf::Keyboard::Left, sf::Event::KeyPressed, Actions::LEFT);
		_aMapper.bindInputToAction(sf::Keyboard::Right, sf::Event::KeyPressed, Actions::RIGHT);
		_aMapper.bindInputToAction(sf::Keyboard::Escape, sf::Event::KeyPressed, Actions::QUIT);
		_reactionMapper->bindActionToReaction<moveDown>(Actions::DOWN);
		_reactionMapper->bindActionToReaction<moveUp>(Actions::UP);
		_reactionMapper->bindActionToReaction<moveLeft>(Actions::LEFT);
		_reactionMapper->bindActionToReaction<moveRight>(Actions::RIGHT);
		_reactionMapper->bindActionToReaction<quit>(Actions::QUIT);
	}
	void update(const sf::Time t)
	{
		if (player.getPosition().x < 0 || player.getPosition().x > 480)
			plVelocity.x = -plVelocity.x;
		if (player.getPosition().y < 0 || player.getPosition().y > 320)
			plVelocity.y = -plVelocity.y;
		player.move(plVelocity * t.asSeconds());
	}
	void draw(sf::RenderWindow &win)
	{
		win.draw(player);
	}
};

int main(int argc, char *argv[])
{
	Test testGame(480, 320, "Hello, World!");
	testGame.run();
	return 0;
}