#include "Player.h"
Player::Player() 
{


//NEED TO ADD ANIMATIONS
	walk.addFrame(sf::IntRect(110, 0, 50, 73));	//WALKING ANIMATION SET
	walk.addFrame(sf::IntRect(160, 0, 50, 73));
	walk.addFrame(sf::IntRect(210, 0, 50, 73));
	walk.addFrame(sf::IntRect(260, 0, 50, 73));
	walk.addFrame(sf::IntRect(315, 0, 50, 73));
	walk.setFrameSpeed(1.f / 10.f);


	sneak.addFrame(sf::IntRect(145, 77, 51, 67));	//CROUCH ANIMATION SET
	sneak.setFrameSpeed(1.f / 4.f);


	idle.addFrame(sf::IntRect(0, 0, 50, 73));	//IDLE ANIMATION
	
	shoot.addFrame(sf::IntRect(49, 0, 53, 73));	//SHOOTING ANIMATION

	flip = false;

	getCurrentAnimation = &idle;	//STARTING ANIMATION IS IDLE
	
	setTextureRect(getCurrentAnimation->getCurrentFrame());

	pSpeed = 80;

	playerGravity = sf::Vector2f(0, 9.8f) * playerScale;	//PLAYER GRAVITY SET
	playerJump = sf::Vector2f(0, -5.0f) * playerScale;
	isJumping = false;
}
Player::~Player()
{

}
void Player::setSpeed(int a)	//GETTERS AND SETTERS
{
	pSpeed=a;
}
int Player::getSpeed()
{
	return pSpeed;
}
void Player::setHealth(int a)
{
	pHealth=a;
}
int Player::getHealth()
{
	return pHealth;
}

void Player::update(float dt,int wX,int wY,Input*input)
{
	sf::Vector2f pos = playerVelocity * dt + 0.5f * playerGravity * dt * dt;	//GRAVITY CALCULATIONS
	playerVelocity += playerGravity * dt;
	setPosition(getPosition() + pos);

	if (getPosition().y >= wY - getSize().y)	//PLAYER CAN'T GO EXIT THE SCREEN
	{
		setPosition(getPosition().x, wY - getSize().y);
		playerVelocity = sf::Vector2f(0, 0);
		isJumping = false;
	}
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		if (!isJumping)
		{
			playerVelocity = playerJump;
			isJumping = true;

		}
	}
	if (getPosition().x < 0)
	{
		float x1 = 0;
		setPosition(x1, getPosition().y);

	}
}
void Player::handleInput(float dt, Input* input)	//ANIMATIONS AND MOVEMENTS SETTINGS FOR THE PLAYER
{
	setTextureRect(walk.getCurrentFrame());
	getCurrentAnimation->animate(dt);
	setTextureRect(getCurrentAnimation->getCurrentFrame());
	if (input->isKeyDown(sf::Keyboard::LShift))	//SPRINT ON KEY INPUT
	{
		pSpeed = 170;
	}
	if (!input->isKeyDown(sf::Keyboard::LShift))
	{
		pSpeed = 120;
	}
	if (input->isKeyDown(sf::Keyboard::D))
	{
		flip = false;
		move(pSpeed * dt, 0);
		getCurrentAnimation = &walk;
		walk.setFlipped(false);
		setTextureRect(getCurrentAnimation->getCurrentFrame());
		idle.setFlipped(false);

	}

	else if (input->isKeyDown(sf::Keyboard::A))
	{
		move(-pSpeed * dt, 0);
		getCurrentAnimation = &walk;
		walk.setFlipped(true);
		setTextureRect(getCurrentAnimation->getCurrentFrame());
		flip = true;
		idle.setFlipped(true);

	}
	else if (input->isKeyDown(sf::Keyboard::S)&&flip==false)
	{

		getCurrentAnimation = &sneak;
		sneak.setFlipped(false);
		setTextureRect(getCurrentAnimation->getCurrentFrame());
		getCurrentAnimation = &idle;
	}
	else if (input->isKeyDown(sf::Keyboard::S)&&flip==true)
	{
		getCurrentAnimation = &sneak;
		sneak.setFlipped(true);
		setTextureRect(getCurrentAnimation->getCurrentFrame());
		getCurrentAnimation = &idle;
	}
	else if (input->isKeyDown(sf::Keyboard::J) && flip == false)
	{

		getCurrentAnimation = &shoot;
		shoot.setFlipped(false);
		setTextureRect(getCurrentAnimation->getCurrentFrame());
		getCurrentAnimation = &idle;
	}
	else if (input->isKeyDown(sf::Keyboard::J) && flip == true)
	{
		getCurrentAnimation = &shoot;
		shoot.setFlipped(true);
		setTextureRect(getCurrentAnimation->getCurrentFrame());
		getCurrentAnimation = &idle;
	}

	else
	{
		getCurrentAnimation->reset();
	}

}
