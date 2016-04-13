#include <Book/Player.hpp>
#include <Book/CommandQueue.hpp>
#include <Book/Aircraft.hpp>
#include <Book/Foreach.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <map>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std::placeholders;


struct AircraftMover
{
	AircraftMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		
		aircraft.accelerate(velocity * aircraft.getMaxSpeed());
	}

	sf::Vector2f velocity;
};

struct AircraftRotator
{
	AircraftRotator(float degree)
		: rotation(degree)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.setRotation(aircraft.getRotation() + rotation);
	}

	float rotation;
};

Player::Player()
: mCurrentMissionStatus(MissionRunning)
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::A] = MoveLeft;
	mKeyBinding[sf::Keyboard::D] = MoveRight;
	mKeyBinding[sf::Keyboard::W] = MoveUp;
	mKeyBinding[sf::Keyboard::S] = MoveDown;
	mKeyBinding[sf::Keyboard::Space] = Fire;
	mKeyBinding[sf::Keyboard::M] = LaunchMissile;
	mKeyBinding[sf::Keyboard::E] = RotateCW;
	mKeyBinding[sf::Keyboard::Q] = RotateCCW;
 
	// Set initial action bindings
	initializeActions();	

	// Assign all categories to player's aircraft
	FOREACH(auto& pair, mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		std::cout << "keypressed" << std::endl;
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
	else if (event.type == sf::Event::MouseButtonReleased){
		std::cout << "mousePressed" << std::endl;
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	
	FOREACH(auto pair, mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::MouseInput(sf::Event& event, sf::RenderWindow &mWindow){

	bool clickedPlay = WithinBox(sf::Mouse::getPosition(mWindow), 415, 606, 303, 345);
	bool clickedSettings = WithinBox(sf::Mouse::getPosition(mWindow), 415, 606, 353, 395);
	bool clickedExit = WithinBox(sf::Mouse::getPosition(mWindow), 415, 606, 403, 445);

	if (clickedPlay)
		std::cout << "clicked Play at" << sf::Mouse::getPosition(mWindow).x << " " << sf::Mouse::getPosition(mWindow).y << std::endl;
	else if (clickedSettings)
		std::cout << "clicked Settings at" << sf::Mouse::getPosition(mWindow).x << " " << sf::Mouse::getPosition(mWindow).y << std::endl;
	else if (clickedExit)
		std::cout << "clicked Exit at" << sf::Mouse::getPosition(mWindow).x << " " << sf::Mouse::getPosition(mWindow).y << std::endl;

	//std::cout << WithinBox( sf::Mouse::getPosition(mWindow), 415,606,303,345);
	//std::cout << sf::Mouse::getPosition(mWindow).x << " " << sf::Mouse::getPosition(mWindow).y << std::endl << std::endl;
}

bool Player::WithinBox(sf::Vector2i mousePos, int minX, int maxX, int minY, int maxY){

	return(mousePos.x >= minX && mousePos.x <= maxX
		&& mousePos.y >= minY && mousePos.y <= maxY);
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	std::cout << "keypressed" << std::endl;
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	FOREACH(auto pair, mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(MissionStatus status)
{
	mCurrentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
	return mCurrentMissionStatus;
}

void Player::initializeActions()
{
	mActionBinding[MoveLeft].action      = derivedAction<Aircraft>(AircraftMover(-1,  0));
	mActionBinding[MoveRight].action     = derivedAction<Aircraft>(AircraftMover(+1,  0));
	mActionBinding[MoveUp].action        = derivedAction<Aircraft>(AircraftMover( 0, -1));
	mActionBinding[MoveDown].action      = derivedAction<Aircraft>(AircraftMover( 0, +1));
	mActionBinding[Fire].action          = derivedAction<Aircraft>([] (Aircraft& a, sf::Time) { a.fire(); });
	mActionBinding[LaunchMissile].action = derivedAction<Aircraft>([] (Aircraft& a, sf::Time) { a.launchMissile(); });
	mActionBinding[RotateCW].action = derivedAction<Aircraft>(AircraftRotator(+1));
	mActionBinding[RotateCCW].action = derivedAction<Aircraft>(AircraftRotator(-1));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveDown:
		case MoveUp:
		case Fire:
		case RotateCW:
		case RotateCCW:
			return true;

		default:
			return false;
	}
}
