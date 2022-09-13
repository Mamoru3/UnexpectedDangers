#include "Bullet.h"
Bullet::Bullet()
{

}
Bullet::~Bullet()
{

}


void Bullet::update(float dt)
{
	move(velocity * dt);
}