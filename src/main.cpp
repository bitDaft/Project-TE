/*
 * File: main.cpp
 * Project: Project-TE
 * Created Date: Sunday June 9th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Saturday, March 28th 2020 6:52:13 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
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
#include "ResourceLoader.hpp"

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
		return true;
	}
	bool moveRightR(sf::Event &)
	{
		plVelocity.x -= playerMoveSpeed;
		return true;
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
		return true;
	}
	bool moveRight(sf::Event &)
	{
		plVelocity.x += playerMoveSpeed;
		return true;
	}

public:
	sf::Vector2f plVelocity;
	AnimatedSprite test;
	sf::Sprite test2;
	sf::Sprite sheet;
	sf::Time ttime;
	~TestPlayer()
	{
	}
	TestPlayer() : IUpdatable(1), IDrawable(1), playerMoveSpeed(50.f), plVelocity(0, 0)
	{
		ttime = sf::seconds(0.f);
		enableInputHandling();
		player.setPosition(100.f, 100.f);
		_reactionMapper->bindActionToReaction<&TestPlayer::moveUpR>(Actions::UP_RELEASE);
		_reactionMapper->bindActionToReaction<&TestPlayer::moveDownR>(Actions::DOWN_RELEASE);
		_reactionMapper->bindActionToReaction<&TestPlayer::moveLeftR>(Actions::LEFT_RELEASE);
		_reactionMapper->bindActionToReaction<&TestPlayer::moveRightR>(Actions::RIGHT_RELEASE);
		_reactionMapper->bindActionToReaction<&TestPlayer::moveDown>(Actions::DOWN);
		_reactionMapper->bindActionToReaction<&TestPlayer::moveUp>(Actions::UP);
		_reactionMapper->bindActionToReaction<&TestPlayer::moveLeft>(Actions::LEFT);
		_reactionMapper->bindActionToReaction<&TestPlayer::moveRight>(Actions::RIGHT);
	}
	void setAnimation(Animation &anim)
	{
		test.setAnimation(anim);
		// test.setAnimation(ResourceManager::getAnimation(1));
		test.setAnimationTime(sf::seconds(1.f));
		test.setScale(2.f, 2.f);
		// test.setPosition(0.f, 0.f);
		// test2.setTexture(ResourceManager::getTexture(1));
		// test2.setPosition(0, 0);
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
		ttime += t;
		if (ttime.asSeconds() > 5.f)
		{
			disableUpdate();
			ttime = sf::seconds(0.f);
		}
		sheet.setPosition(0, 0);
		test.update(t);
	}
	void disabledUpdate(const sf::Time &t)
	{
		ttime += t;
		if (ttime.asSeconds() > 2.f)
		{
			enableUpdate();
			ttime = sf::seconds(0.f);
		}
		test.update(t);
	}
	void draw(const sf::Time &, sf::RenderTexture &tex)
	{
		// we dont really want a draw here
		// what we want is to send the vertices so that they may all be drawn at the same time
		tex.draw(test);
		// tex.draw(test2);
		// tex.draw(player);
	}
};

class Test : public Game, private IUpdatable
{
private:
	TestPlayer pl2;
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
		std::cout << "Moving : " << e.mouseMove.x << " " << e.mouseMove.y << "\n";
		return false;
	}
	bool ms(sf::Event &)
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
				pl2(),
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
		}
	}

	void init()
	{
		ResourceLoader rs;
		bool t = rs.loadFile("./boot.teldr");
		if (t)
		{
			rs.load();
			ResourceManager::getLoader(1).load();
			auto t1 = ResourceManager::getAnimation(1);
		}
		else
		{
			std::cout << "failed loading boot file";
		}
		pl2.setAnimation(ResourceManager::getAnimation(1));

		_reactionMapper->bindActionToReaction<&Test::mld>(Actions::MOUSE_LEFT);
		_reactionMapper->bindActionToReaction<&Test::mlu>(Actions::MOUSE_LEFT_RELEASE);
		_reactionMapper->bindActionToReaction<&Test::mrd>(Actions::MOUSE_RIGHT);
		_reactionMapper->bindActionToReaction<&Test::mru>(Actions::MOUSE_RIGHT_RELEASE);
		_reactionMapper->bindActionToReaction<&Test::mm>(Actions::MOUSE_MOVED);
		_reactionMapper->bindActionToReaction<&Test::ms>(Actions::MOUSE_SCROLL);
		_reactionMapper->bindActionToReaction<&Test::quit>(Actions::QUIT);

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
	Game *testGame = new Test(480, 320, "Untitled 1");
	testGame->run();

	return 0;
}