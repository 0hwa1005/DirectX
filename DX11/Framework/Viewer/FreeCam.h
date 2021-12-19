#pragma once
#include "Camera.h"
class FreeCam :
	public Camera
{
public:
	FreeCam();
	~FreeCam();

	void Update() override;
	void Speed(float move, float rotation);

private:
	float move;
	float rotation;
};

