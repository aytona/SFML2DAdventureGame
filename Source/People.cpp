#include <Book/People.hpp>
#include <Book/DataTables.hpp>
#include <Book/Category.hpp>
#include <Book/CommandQueue.hpp>
#include <Book/Utility.hpp>
#include <Book/ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace
{
	const std::vector<PeopleData> Table = initializePeopleData();
}

People::People(Type type, const TextureHolder& textures) 
	: Entity(1), 
	mType(type), 
	mSprite(textures.get(Table[type].texture), 
	Table[type].textureRect)
{
	centerOrigin(mSprite);
}

unsigned int People::getCategory() const
{
	return Category::People;
}

sf::FloatRect People::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void People::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}