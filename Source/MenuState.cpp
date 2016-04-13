#include <Book/MenuState.hpp>
#include <Book/Button.hpp>
#include <Book/Utility.hpp>
#include <Book/ResourceHolder.hpp>
#include <Book/Player.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>




MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
, mTitle()
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	mBackgroundSprite.setTexture(texture);

	mTitle.setFont(context.fonts->get(Fonts::Main));
	mTitle.setCharacterSize(70);
	mTitle.setString("Alien Invasion");
	centerOrigin(mTitle);
	mTitle.setPosition(sf::Vector2f(context.window->getSize().x / 2u, 150.f));

	auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->setPosition(512 - (350 / 2), 300);
	playButton->setText("Play");
	playButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(States::LevelOne);
		//currentState = States::LevelOne;
	});

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	settingsButton->setPosition(512 - (350 / 2), 350);
	settingsButton->setText("Settings");
	settingsButton->setCallback([this] ()
	{
		requestStackPush(States::Settings);
		//currentState = States::Settings;
	});

	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exitButton->setPosition(512 - (350 / 2), 400);
	exitButton->setText("Exit");
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	mGUIContainer.pack(playButton);
	mGUIContainer.pack(settingsButton);
	mGUIContainer.pack(exitButton);

	//Player p = Player();

//	p.SetCurrentState("menu");

	currentState = "Menu";

	//std::cout << currentState << std::endl;

//	std::cout << "menu open" << std::endl;
}

void MenuState::PlayGame(){
	requestStackPop();
	requestStackPush(States::LevelOne);
}


void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
	window.draw(mTitle);

	
	//std::cout << "menu state" << std::endl;
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{


	
	

		//std::cout << currentState << event.type << std::endl;

		//std::cout << "handling event" << std::endl;
		mGUIContainer.handleEvent(event);
	
	return false;
}
