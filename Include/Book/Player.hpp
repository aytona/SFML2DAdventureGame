#ifndef BOOK_PLAYER_HPP
#define BOOK_PLAYER_HPP

#include <Book/Command.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <map>


class CommandQueue;

class Player
{
	public:
		enum Action
		{
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			Fire,
			LaunchMissile,
			RotateCW,
			RotateCCW,
			ActionCount
		};

		enum MissionStatus
		{
			MissionRunning,
			MissionSuccess,
			MissionFailure
		};


	public:
								Player();

		void					handleEvent(const sf::Event& event, CommandQueue& commands);
		void					handleRealtimeInput(CommandQueue& commands);

		void					assignKey(Action action, sf::Keyboard::Key key);
		sf::Keyboard::Key		getAssignedKey(Action action) const;

		void 					setMissionStatus(MissionStatus status);
		MissionStatus 			getMissionStatus() const;
		void					 MouseInput(sf::Event& event, sf::RenderWindow &mWindow);
		bool					WithinBox(sf::Vector2i mousePos, int minX, int maxX, int minY, int maxY);

	private:
		void					initializeActions();
		static bool				isRealtimeAction(Action action);


	private:
		std::map<sf::Keyboard::Key, Action>		mKeyBinding;
		std::map<Action, Command>				mActionBinding;
		MissionStatus 							mCurrentMissionStatus;
};

#endif // BOOK_PLAYER_HPP
