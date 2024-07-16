#pragma once
#include "Enemies.hpp"

namespace msp
{
	class Enemy1 : public Enemies
	{
	public:
		Enemy1() = default;
		virtual ~Enemy1() {}

		void SpecialAbility() override;

	};
}
