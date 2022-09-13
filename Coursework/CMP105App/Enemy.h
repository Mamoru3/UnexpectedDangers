#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include<string>
#include <iostream>
class Enemy : public GameObject
{
private:
	int eHealth;
	int eSpeed;


public:
	Enemy();
	~Enemy();

	void setSpeed(int a);
	int getSpeed();
	void setHealth(int a);
	int getHealth();

	float eScale = 200.f;
	float eAcceleration = 200.f;

	void update(float dt, int wX, int wY);

	Animation eWalk;
	Animation* getCurrentAnimation;

	sf::Vector2f  eGravity, eVelocity;
	sf::Clock eClock;
	sf::Time eTime1;

};

