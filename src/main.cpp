/*
 * File: main.cpp
 * Project: Project-TE
 * Created Date: Sunday June 9th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday December 24th 2019 10:16:56 am
 * Modified By: bitDaft at <ajaxhis@tutanota.com>
 * -----
 * Copyright (c) 2019 bitDaft coorp.
 */

#include <iostream>
#include <vector>
#include "Game.hpp"
#include "ResourceManager.hpp"
#include "test.hpp"
#include "IUpdatable.hpp"
#include "IDrawable.hpp"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"

enum EventType
{
	testNum = sf::Event::EventType::Count + 1,
	testNum2
};

// ?maybe move this into lib since we can fix every input event with input actions
// ?It may be inefficient but coder will not have to do crap.. just link callback to action
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

class TestPlayer : public InputHandler, private IUpdatable, private IDrawable
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
	Animation testani;
	AnimatedSprite test;
	sf::Sprite sheet;
	~TestPlayer()
	{
	}
	TestPlayer() : IUpdatable(1), IDrawable(1), playerMoveSpeed(50.f), plVelocity(0, 0), testani(6)
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
		const unsigned int sheetHandle = ResourceManager::loadTexture("assets/sheet2.png");
		sheet.setTexture(ResourceManager::getTexture(sheetHandle));
		testani.setTexture(ResourceManager::getTexture(sheetHandle));
		testani.addFrame(new sf::IntRect(32, 0, 32, 32));
		testani.addFrame(new sf::IntRect(64, 0, 32, 32));
		testani.addFrame(new sf::IntRect(32, 0, 32, 32));
		testani.addFrame(new sf::IntRect(0, 0, 32, 32));
		test.setAnimation(testani);
		test.setAnimationTime(sf::seconds(1.5f));
		test.setScale(2.f, 2.f);
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
		test.move(t);
	}
	const sf::Sprite &getSprite()
	{
		return player;
	}
	void update(const sf::Time &t)
	{
		if (getPosition().x < 0 || getPosition().x > 480)
			plVelocity.x = -plVelocity.x;
		if (getPosition().y < 0 || getPosition().y > 320)
			plVelocity.y = -plVelocity.y;
		move(plVelocity * t.asSeconds());
		sheet.setPosition(0, 0);
		test.update(t);
	}
	void draw(const sf::Time &t, sf::RenderTexture &tex)
	{
		// we dont really want a draw here
		// what we want is to send the vertices so that they may all be drawn at the same time
		tex.draw(test);
		// tex.draw(player);
	}
};
class A : IUpdatable
{
public:
	A() : IUpdatable(1)
	{
	}
	~A()
	{
	}
	void update(const sf::Time &t)
	{
	}
};

class Test : public Game, private IUpdatable
{
private:
	TestPlayer pl;
	sf::Time tt;

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
		// std::cout << "Moving : " << e.mouseMove.x << " " << e.mouseMove.y << "\n";
		return false;
	}
	bool ms(sf::Event &e)
	{
		// std::cout << "Scrolling : " << e.mouseWheelScroll.delta << "\n";
		return false;
	}

public:
	~Test()
	{
	}
	Test(const int wndWidth, const int wndHeight, const char *wndName)
			: Game(wndWidth, wndHeight, wndName),
				IUpdatable(1),
				pl(),
				tt(sf::Time::Zero)
	{

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
	}
	void update(const sf::Time &t)
	{
		tt += t;
		if (tt.asSeconds() > 1)
		{
			tt -= sf::seconds(1.f);
			A a;
		}
	}

	void init()
	{

		const unsigned int playerHandle = ResourceManager::loadTexture("assets/player.png");
		pl.settexture(ResourceManager::getTexture(playerHandle));

		// TODO: change it so that diff key same action when pressed twice does not trigger twice

		_reactionMapper->bindActionToReaction<mld>(Actions::MOUSE_LEFT);
		_reactionMapper->bindActionToReaction<mlu>(Actions::MOUSE_LEFT_RELEASE);
		_reactionMapper->bindActionToReaction<mrd>(Actions::MOUSE_RIGHT);
		_reactionMapper->bindActionToReaction<mru>(Actions::MOUSE_RIGHT_RELEASE);
		_reactionMapper->bindActionToReaction<mm>(Actions::MOUSE_MOVED);
		_reactionMapper->bindActionToReaction<ms>(Actions::MOUSE_SCROLL);
		_reactionMapper->bindActionToReaction<quit>(Actions::QUIT);

		_inputManager.pushEntity(&pl);

		// testData *t = new testData();
		// gameWindow.triggerEvent(EventType::testNum, t);
		// gameWindow.triggerEvent(EventType::testNum2, new int(200));
	}
	void processCustomEvents(Event &event)
	{
		switch (event.type)
		{
		// case EventType::testNum:
		// {
		// 	testData e;
		// 	if (event.getData(e))
		// 	{
		// 		debug(e.x);
		// 	}
		// 	break;
		// }
		// case EventType::testNum2:
		// {
		// 	int e;
		// 	if (event.getData(e))
		// 	{
		// 		debug(e);
		// 	}
		// 	break;
		// }
		default:
			break;
		}
	}
	// void draw(const sf::Time &t)
	// {
	// 	gameWindow.draw(pl.getSprite());
	// }
	void end()
	{
	}
};

int main()
{
	Game *testGame = new Test(480, 320, "Hello, World!");
	testGame->run();
	return 0;
}