#pragma once

#include <Book/State.hpp>
#include <Book/World.hpp>
#include <Book/Player.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class LevelTwo : public State
{
public:
	LevelTwo(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	World				mWorld;
	Player&				mPlayer;
	sf::Text			mPeopleCounter;
};