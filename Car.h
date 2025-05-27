#pragma once
#include "raylib.h"
#include "AssetBank.h"
#include "Utils.h"
#include "Track.h"

struct CarControls
{
	int turnRight;
	int turnLeft;
	int accelerate;
	int brake;
};

class Car
{
private:
	Vector2 mPosition;
	Vector2 mSize;

	Vector2 mVelocity;
	Vector2 mDirection;

	float mTurnSpeed;
	float mAccelRate;
	float mMaxFriction;
	float mMinFriction;
	float mMaxSpeed;

	CarControls mControls;

	Track* mTrackPtr;

public:
	Car();
	~Car();

	Car(Vector2 position, Vector2 size, Vector2 direction, Track* trackPtr, float turnSpeed, float accel, float maxSpeed, CarControls controls);

	void Update();
	void Draw() const;

	Vector2 GetPosition() const;
	Vector2 GetSize() const;
	Vector2 GetDirection() const;
};

