#ifndef BOOK_CATEGORY_HPP
#define BOOK_CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		SceneAirLayer		= 1 << 0,
		People				= 1 << 1,
		PlayerAircraft		= 1 << 2,
		AlliedAircraft		= 1 << 3,
		EnemyAircraft		= 1 << 4,
		PeopleAircraft		= 1 << 5,
		Pickup				= 1 << 6,
		AlliedProjectile	= 1 << 7,
		EnemyProjectile		= 1 << 8,
		ParticleSystem		= 1 << 9,
		

		Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,
		Projectile = AlliedProjectile | EnemyProjectile,
	};
}

#endif // BOOK_CATEGORY_HPP
