#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class Chains : public GameObject
{
public:
	Chains(float left, float top, float width, float height);

	void Render();

	~Chains();
};

