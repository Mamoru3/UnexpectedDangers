#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Player:public GameObject
{
	

	int pHealth;
	int pSpeed;
public:
	Player();
	~Player();

	void setSpeed(int a);
	int getSpeed();
	void setHealth(int a);
	int getHealth();

	
	float playerScale = 120.f;
	float playerAcceleration = 200.f;

	sf::Vector2f  playerGravity, playerVelocity, playerJump;


	bool flip;
	bool isJumping;

	void handleInput(float dt, Input* input);
	void update(float dt,int wX,int wY,Input*input) ;

	
	Animation walk;
	Animation idle;
	Animation sneak;
	Animation shoot;
	Animation* getCurrentAnimation;
};

