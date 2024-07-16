#include "Bullet.hpp"
#include <cmath>

namespace msp
{

	Bullet::Bullet(float x, float y, float r, float v, float alpha)
	{
		Setup(x, y, r, v, alpha);
	}

	void Bullet::Setup(float x, float y, float r, float v, float alpha)
	{
		this->x = x;
		this->y = y;
		this->r = r;
		this->v = v;
		this->alpha = alpha;
		m_shape.setOrigin(r, r);
		m_shape.setRadius(r);
		m_shape.setPosition(x, y);
		int color_r = 255;
		int color_g = 0;
		int color_b = 0;
		m_shape.setFillColor(sf::Color(color_r, color_b, color_g, 255));
	}

	sf::CircleShape Bullet::Get()
	{
		return m_shape;
	}

	float Bullet::X() { return x; }
	void Bullet::X(float value) { x = value; m_shape.setPosition(x, y); }
	void Bullet::Y(float value) { y = value; m_shape.setPosition(x, y); }
	float Bullet::Y() { return y; }
	float Bullet::R() { return r; }
	float Bullet::V() { return v; }
	void Bullet::V(float value) { v = value; }

	void Bullet::Move(float dt)
	{
		float alphaRad = acos(-1) * alpha / 180;
		x += v * cos(alphaRad) * dt;
		y += v * sin(alphaRad) * dt;
		m_shape.setPosition(x, y);
	}

	void Bullet::setVelocity(float dv, float dt)
	{
		float alphaRad = acos(-1) * alpha / 180;
		v += dv * dt;
	}

}

