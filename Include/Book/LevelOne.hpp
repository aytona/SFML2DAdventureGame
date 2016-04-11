#ifndef BOOK_LEVELONE_HPP
#define BOOK_LEVELONE_HPP

#include <Book/State.hpp>
#include <Book/World.hpp>
#include <Book/Player.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class LevelOne : public State
{
	public:
							LevelOne(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		World				mWorld;
		Player&				mPlayer;
		sf::Text			mPeopleCounter;
		float				mPeopleAmount;
};

#endif // BOOK_GAMESTATE_HPP