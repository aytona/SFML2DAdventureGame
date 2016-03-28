#pragma once

#include <Book/Entity.hpp>
#include <Book/Command.hpp>
#include <Book/ResourceIdentifiers.hpp>

#include <SFML/Graphics/Sprite.hpp>

class Aircraft;

class People : public Entity
{
public:
	enum Type
	{
		Solo,
		Group,
		TypeCount
	};

public:
	People(Type type, const TextureHolder& textures);

	virtual unsigned int		getCategory() const;
	virtual sf::FloatRect		getBoundingRect() const;

	void						apply(Aircraft& player) const;		// Might not need this. TODO: Look into this

protected:
	virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type						mType;
	sf::Sprite					mSprite;
};