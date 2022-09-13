#include "Enemy.h"
Enemy::Enemy()
{
	eWalk.addFrame(sf::IntRect(0, 912, 825, 933));	//BOSS WALK ANIMATION SET
	eWalk.addFrame(sf::IntRect(825, 912, 825, 933));
	eWalk.addFrame(sf::IntRect(1650, 912, 825, 933));
	eWalk.addFrame(sf::IntRect(2475, 912, 825, 933));
	eWalk.setFrameSpeed(1.f / 10.f);

	getCurrentAnimation = &eWalk;
	setTextureRect(getCurrentAnimation->getCurrentFrame());

	eScale = 200.f;
	eAcceleration = 200.f;

	eGravity = sf::Vector2f(0, 9.8f) * eScale;
	
	
}
Enemy::~Enemy()
{

}
void Enemy::setSpeed(int a)
{
	eSpeed = a;
}
int Enemy::getSpeed()
{
	return eSpeed;
}
void Enemy::setHealth(int a)
{
	eHealth = a;
}
int Enemy::getHealth()
{
	return eHealth;
}

void Enemy::update(float dt, int wX, int wY)
{
	eTime1 = eClock.getElapsedTime();	//clock set for enemies

	sf::Vector2f pos = velocity * dt + 0.5f * eGravity * dt * dt;	//BOSS GRAVITY APPLIED
	velocity += eGravity * dt;
	setPosition(getPosition() + pos);

	setTextureRect(eWalk.getCurrentFrame());
	getCurrentAnimation->animate(dt);

	if (eTime1.asSeconds() >= 3)	
	{
		getCurrentAnimation = &eWalk;
		move(-getSpeed() * dt, 0);
	}

	if (getPosition().y >= wY - getSize().y) //BOSS WON'T EXIT THE SCREEN
	{
		setPosition(getPosition().x, wY - getSize().y);
		velocity = sf::Vector2f(0, 0);

	}
}




