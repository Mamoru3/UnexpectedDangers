#include "Boss.h"
Boss::Boss()
{
	bWalk.addFrame(sf::IntRect(0, 2, 132, 125));	//BOSS WALK ANIMATION SET
	bWalk.addFrame(sf::IntRect(133, 2, 132, 125));
	bWalk.addFrame(sf::IntRect(267, 2, 132, 125));
	bWalk.addFrame(sf::IntRect(403, 2, 132, 125));
	bWalk.setFrameSpeed(1.f / 8.f);

	//NEED TO ADD THE CROUCH AND JUMP ANIMATION


	bIdle.addFrame(sf::IntRect(0, 2, 132, 125));		//BOSS IDLE ANIMATION
	bIdle.setFrameSpeed(1.f/ 10.f);

	getCurrentAnimation = &bIdle;	//BOSS START BY BEING IDLE

	bIdle.setFlipped(true);
	bWalk.setFlipped(true);

	setTextureRect(getCurrentAnimation->getCurrentFrame());

	bossCounter = 1;	//BOSS COUNTER FOR BULLETS ALTERANTION

	bossGravity = sf::Vector2f(0, 9.8f) * bossScale;	//BOSS GRAVITY SET
	
}

Boss::~Boss()
{

}

void Boss::setSpeed(int a)	//GETTERS AND SETTERS
{
	bSpeed = a;
}
int Boss::getSpeed()
{
	return bSpeed;
}
void Boss::setHealth(int a)
{
	bHealth = a;
}
int Boss::getHealth()
{
	return bHealth;
}
void Boss::setBulletDamage(int a)
{
	bulletDamage = a;
}
int Boss::getBulletDamage()
{
	return bulletDamage;
}

void Boss::update(float dt,int wX,int wY)	//BOSS UPDATE FUNCTIONS
{
	sf::Vector2f pos = velocity * dt + 0.5f * bossGravity * dt * dt;	//BOSS GRAVITY APPLIED
	velocity += bossGravity * dt;
	setPosition(getPosition() + pos);

	if (getPosition().y >= wY - getSize().y) //BOSS WON'T EXIT THE SCREEN
	{
		setPosition(getPosition().x, wY - getSize().y);
		velocity = sf::Vector2f(0, 0);
	
	}
	
	bTime1= bClock.getElapsedTime();	//CLOCK SET FOR BULLETS
	setTextureRect(bWalk.getCurrentFrame());
	getCurrentAnimation->animate(dt);
	setTextureRect(getCurrentAnimation->getCurrentFrame());

	if(bTime1.asSeconds()>=5)	//BOSS START WALKING AFTER A BIT
	{ 
		getCurrentAnimation = &bWalk;
		move(-getSpeed()*dt, 0);
	}


}