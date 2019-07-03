/*
 * File: main.cpp
 * Project: Project-TE
 * Created Date: Sunday June 9th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Wednesday July 3rd 2019 2:39:05 pm
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include <iostream>
#include "Game.hpp"

enum Actions
{
	MOUSE_LEFT,
	MOUSE_LEFT_RELEASE,
	MOUSE_RIGHT,
	MOUSE_RIGHT_RELEASE,
	MOUSE_MIDDLE,
	MOUSE_MIDDLE_RELEASE,
	MOUSE_X1,
	MOUSE_X1_RELEASE,
	MOUSE_X2,
	MOUSE_X2_RELEASE,
	MOUSE_MOVED,
	MOUSE_SCROLL,
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

class TestPlayer : public InputHandler
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
	~TestPlayer() {}
	TestPlayer() : InputHandler(this), playerMoveSpeed(50.f), plVelocity(0, 0)
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

	bool mld(sf::Event &)
	{
		std::cout << "Pressed left\n";
		return false;
	}
	bool mlu(sf::Event &)
	{
		std::cout << "Released left\n";
		return false;
	}
	bool mrd(sf::Event &)
	{
		std::cout << "Pressed right\n";
		return false;
	}
	bool mru(sf::Event &)
	{
		std::cout << "Released right\n";
		return false;
	}
	bool mm(sf::Event &e)
	{
		std::cout << "Moving : " << e.mouseMove.x << " " << e.mouseMove.y << "\n";
		return false;
	}
	bool ms(sf::Event &e)
	{
		std::cout << "Scrolling : " << e.mouseWheelScroll.delta << "\n";
		return false;
	}

public:
	Test(const int wndWidth, const int wndHeight, const char *wndName) : Game(wndWidth, wndHeight, wndName), pl()
	{
	}

	void init()
	{
		const unsigned int playerHandle = ResourceManager::loadTexture("assets/player.png");
		pl.settexture(ResourceManager::getTexture(playerHandle));

		// TODO: change it so that diff key same action when pressed twice does not trigger twice

		_aMapper.bindInputToAction(sf::Keyboard::Up, sf::Event::KeyPressed, Actions::UP);
		_aMapper.bindInputToAction(sf::Keyboard::Up, sf::Event::KeyReleased, Actions::UP_RELEASE);
		_aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyPressed, Actions::DOWN);
		_aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyReleased, Actions::DOWN_RELEASE);
		_aMapper.bindInputToAction(sf::Keyboard::Left, sf::Event::KeyPressed, Actions::LEFT);
		_aMapper.bindInputToAction(sf::Keyboard::Left, sf::Event::KeyReleased, Actions::LEFT_RELEASE);
		_aMapper.bindInputToAction(sf::Keyboard::Right, sf::Event::KeyPressed, Actions::RIGHT);
		_aMapper.bindInputToAction(sf::Keyboard::Right, sf::Event::KeyReleased, Actions::RIGHT_RELEASE);
		_aMapper.bindInputToAction(sf::Keyboard::Escape, sf::Event::KeyPressed, Actions::QUIT);
		_aMapper.bindInputToAction(sf::Keyboard::W, sf::Event::KeyPressed, Actions::UP);
		_aMapper.bindInputToAction(sf::Keyboard::W, sf::Event::KeyReleased, Actions::UP_RELEASE);
		_aMapper.bindInputToAction(sf::Keyboard::S, sf::Event::KeyPressed, Actions::DOWN);
		_aMapper.bindInputToAction(sf::Keyboard::S, sf::Event::KeyReleased, Actions::DOWN_RELEASE);
		_aMapper.bindInputToAction(sf::Keyboard::A, sf::Event::KeyPressed, Actions::LEFT);
		_aMapper.bindInputToAction(sf::Keyboard::A, sf::Event::KeyReleased, Actions::LEFT_RELEASE);
		_aMapper.bindInputToAction(sf::Keyboard::D, sf::Event::KeyPressed, Actions::RIGHT);
		_aMapper.bindInputToAction(sf::Keyboard::D, sf::Event::KeyReleased, Actions::RIGHT_RELEASE);

		_aMapper.bindInputToAction(sf::Mouse::Button::Left, sf::Event::MouseButtonPressed, Actions::MOUSE_LEFT);
		_aMapper.bindInputToAction(sf::Mouse::Button::Left, sf::Event::MouseButtonReleased, Actions::MOUSE_LEFT_RELEASE);
		_aMapper.bindInputToAction(sf::Mouse::Button::Right, sf::Event::MouseButtonPressed, Actions::MOUSE_RIGHT);
		_aMapper.bindInputToAction(sf::Mouse::Button::Right, sf::Event::MouseButtonReleased, Actions::MOUSE_RIGHT_RELEASE);
		_aMapper.bindInputToAction(sf::Mouse::Button::Middle, sf::Event::MouseButtonPressed, Actions::MOUSE_MIDDLE);
		_aMapper.bindInputToAction(sf::Mouse::Button::Middle, sf::Event::MouseButtonReleased, Actions::MOUSE_MIDDLE_RELEASE);
		_aMapper.bindInputToAction(sf::Mouse::Button::XButton1, sf::Event::MouseButtonPressed, Actions::MOUSE_X1);
		_aMapper.bindInputToAction(sf::Mouse::Button::XButton1, sf::Event::MouseButtonReleased, Actions::MOUSE_X1_RELEASE);
		_aMapper.bindInputToAction(sf::Mouse::Button::XButton2, sf::Event::MouseButtonPressed, Actions::MOUSE_X2);
		_aMapper.bindInputToAction(sf::Mouse::Button::XButton2, sf::Event::MouseButtonReleased, Actions::MOUSE_X2_RELEASE);
		_aMapper.bindInputToAction(sf::Event::MouseMoved, Actions::MOUSE_MOVED);
		_aMapper.bindInputToAction(sf::Event::MouseWheelScrolled, Actions::MOUSE_SCROLL);

		_reactionMapper->bindActionToReaction<mld>(Actions::MOUSE_LEFT);
		_reactionMapper->bindActionToReaction<mlu>(Actions::MOUSE_LEFT_RELEASE);
		_reactionMapper->bindActionToReaction<mrd>(Actions::MOUSE_RIGHT);
		_reactionMapper->bindActionToReaction<mru>(Actions::MOUSE_RIGHT_RELEASE);
		_reactionMapper->bindActionToReaction<mm>(Actions::MOUSE_MOVED);
		_reactionMapper->bindActionToReaction<ms>(Actions::MOUSE_SCROLL);
		_reactionMapper->bindActionToReaction<quit>(Actions::QUIT);

		_inputManager.pushEntity(&pl);
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