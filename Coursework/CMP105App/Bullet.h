#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
class Bullet : public GameObject
{
	
public:
	Bullet();
	~Bullet();

	void update(float dt);
};

