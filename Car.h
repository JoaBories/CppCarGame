#pragma once
#include "raylib.h"
#include "AssetBank.h"
#include "Utils.h"


class Car
{
private:
	Vector2 mPosition;
	Vector2 mSize;

	Vector2 mVelocity;
	Vector2 mDirection;

	float mTurnSpeed;

public:
	Car();
	~Car();

	Car(Vector2 position, Vector2 size, Vector2 direction, float turnSpeed);

	void Update();
	void Draw() const;
};

