#include "Enemy1.hpp"

namespace msp
{
	void Enemy1::SpecialAbility()
	{
		x += vx * 4;
		y += vy * 4;
	}
}
