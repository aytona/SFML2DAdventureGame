#include <Book/LevelTwo.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Book/Utility.hpp>

LevelTwo::LevelTwo(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.window, *context.fonts)
	, mPlayer(*context.player)
	, mPeopleCounter()
{
	mPlayer.setMissionStatus(Player::MissionRunning);
	mPeopleCounter.setFont(context.fonts->get(Fonts::Main));
	mPeopleCounter.setCharacterSize(25);
	mPeopleCounter.setString("Level Two");
	centerOrigin(mPeopleCounter);
	mPeopleCounter.setPosition(sf::Vector2f(context.window->getSize().x / 2u, 50.f));
}

void LevelTwo::draw()
{
	mWorld.draw();
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mPeopleCounter);
}

bool LevelTwo::update(sf::Time dt)
{
	mWorld.update(dt);

	if (!mWorld.hasAlivePlayer())
	{
		mPlayer.setMissionStatus(Player::MissionFailure);
		requestStackPush(States::GameOver);
	}

	else if (mWorld.hasPlayerFinishedLevelTwo())
	{
		
		mPlayer.setMissionStatus(Player::MissionSuccess);
		requestStackPush(States::GameOver);
	}

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

bool LevelTwo::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}