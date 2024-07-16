#pragma once
#include "Enemies.hpp"

namespace msp
{
	class Enemy2 : public Enemies
	{
	public:
		Enemy2() = default;
		virtual ~Enemy2() {};

		void SpecialAbility() override;

	};
}
