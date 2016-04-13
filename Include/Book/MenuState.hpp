#ifndef BOOK_MENUSTATE_HPP
#define BOOK_MENUSTATE_HPP

#include <Book/State.hpp>
#include <Book/Container.hpp>
#include <Book/Player.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class MenuState : public State
{
	public:
								MenuState(StateStack& stack, Context context);

		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleEvent(const sf::Event& event);
		void					MenuState::PlayGame();


	private:
		sf::Sprite				mBackgroundSprite;
		GUI::Container			mGUIContainer;
		sf::Text				mTitle;
};

#endif // BOOK_MENUSTATE_HPP
