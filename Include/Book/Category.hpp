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
		Pickup				= 1 << 5,
		AlliedProjectile	= 1 << 6,
		EnemyProjectile		= 1 << 7,
		ParticleSystem		= 1 << 8,
		

		Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,
		Projectile = AlliedProjectile | EnemyProjectile,
	};
}

#endif // BOOK_CATEGORY_HPP
