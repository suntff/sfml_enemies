#pragma once
#include <Enemies.hpp>

namespace msp
{
	class Enemy3 : public msp::Enemies
	{
	public:
		Enemy3() = default;
		virtual ~Enemy3() {}

		void SpecialAbility() override;
	};
}