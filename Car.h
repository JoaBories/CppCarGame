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

struct SkidMark {
	Vector2 position;
	float rotation;
	double lifetime;
};

class Car
{
private:
	Vector2 mPosition;
	Vector2 mSize;

	Vector2 mVelocity;
	Vector2 mDirection;

	vector<SkidMark*> mSkidMarks;
	float mSkidMarkLifetime;

	float mTurnSpeed;
	float mAccelRate;
	float mMaxFriction;
	float mMinFriction;
	float mMaxSpeed;

	int mNumber;

	bool mHasCheckpoint;
	int mLapCount;
	float mBestLapTime;
	float mCurrentLapStartTime;

	CarControls mControls;

	Track* mTrackPtr;

	void CheckCollisions();
	void CheckObstacles();
	void CheckScreenBounds();

	void ResolveCollision(Vector2 resolutionVector);

	void SpawnSkidMark();

	void UpdateSkidMarks();
	

public:
	Car();
	~Car();

	Car(Vector2 position, Vector2 size, Vector2 direction, Track* trackPtr, float turnSpeed, float accel, float maxSpeed, CarControls controls, int number);

	void Update();
	void Draw() const;
	void DrawSkidMarks() const;

	Vector2 GetPosition() const;
	Vector2 GetSize() const;
	Vector2 GetDirection() const;

	bool HasCheckpoint() const;
	void SetHasCheckpoint(bool hasCheckpoint);

	int GetLapCount() const;

	float GetBestLapTime() const;
	float GetCurrentLapTime() const;
	void StartCurrentLap();
	void FinishLap();

};

