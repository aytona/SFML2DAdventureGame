#include <Book/LevelOne.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Book/Utility.hpp>

LevelOne::LevelOne(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.fonts)
, mPlayer(*context.player)
, mPeopleCounter()
, mPeopleAmount()
{
	mPlayer.setMissionStatus(Player::MissionRunning);
	mPeopleCounter.setFont(context.fonts->get(Fonts::Main));
	mPeopleCounter.setCharacterSize(25);
	mPeopleCounter.setString("Level One");
	centerOrigin(mPeopleCounter);
	mPeopleCounter.setPosition(sf::Vector2f(context.window->getSize().x / 2u, 50.f));

}

void LevelOne::draw()
{
	mWorld.draw();
	
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mPeopleCounter);
}

bool LevelOne::update(sf::Time dt)
{
	mWorld.update(dt);

	if (!mWorld.hasAlivePlayer())
	{
		mPlayer.setMissionStatus(Player::MissionFailure);
		requestStackPush(States::GameOver);
	}

	// Counter

	else if (mWorld.hasPlayerFinishedLevelOne())
	{
		requestStateClear();
		requestStackPush(States::LevelTwo);
	}

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

bool LevelOne::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}