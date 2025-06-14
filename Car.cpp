#include "Car.h"

void Car::CheckCollisions()
{
	CheckObstacles();

	CheckScreenBounds();
}

void Car::CheckObstacles()
{
	Rectangle carRect = { mPosition.x, mPosition.y, mSize.x, mSize.y };
	float carRot = Utils::RotFromVector2(mDirection) + 90;

	float minDistance = Utils::Max(mSize.x, mSize.y) * 3;
	minDistance *= minDistance;

	for (const auto& obstacle : mTrackPtr->GetTrackObjects()->GetObstacles())
	{
		float sqrDistance = Utils::SqrLenght(Utils::Vector2Substract({ mPosition.x, mPosition.y }, obstacle.GetPosition()));
		if (sqrDistance <= minDistance)
		{
			Rectangle obstacleRect = { obstacle.GetPosition().x, obstacle.GetPosition().y, obstacle.GetSize().x, obstacle.GetSize().y };

			OBBCollision result = Utils::CheckOBB(carRect, carRot, obstacleRect, 0);

			if (result.collision)
			{
				Vector2 resolution = Utils::Vector2Scale(result.minTranslationAxis, result.minTranslationOverlap);
				Vector2 direction = Utils::Vector2Substract(mPosition, obstacle.GetPosition());

				if (Utils::DotProduct(direction, resolution) < 0)
				{
					resolution = Utils::Vector2Negate(resolution);
				}

				if (Utils::SqrLenght(resolution) > 0)
				{
					ResolveCollision(resolution);
				}
			}
		}
	}
}

void Car::CheckScreenBounds()
{
	Rectangle carRect = { mPosition.x, mPosition.y, mSize.x, mSize.y };
	float carRot = Utils::RotFromVector2(mDirection) + 90;

	Vector2 resolution = { 0, 0 };

	for (const Vector2& corner : Utils::GetCorners(carRect, carRot)) 
	{
		if (corner.x < 0)
		{
			resolution.x -= corner.x;
		}
		if (corner.x > GetScreenWidth())
		{
			resolution.x += GetScreenWidth() - corner.x;
		}
		if (corner.y < 0)
		{
			resolution.y -= corner.y;
		}
		if (corner.y > GetScreenHeight())
		{
			resolution.y += GetScreenHeight() - corner.y;
		}
	}

	if (Utils::SqrLenght(resolution) > 0)
	{
		ResolveCollision(resolution);
	}
}

void Car::ResolveCollision(Vector2 resolutionVector)
{
	mPosition = Utils::Vector2Add(mPosition, resolutionVector);
	
	Vector2 axis = Utils::Normalize(resolutionVector);
	Vector2 perpendicular = Utils::Vector2Scale( axis, Utils::DotProduct(mVelocity, axis));

	mVelocity = Utils::Vector2Substract(mVelocity, perpendicular);
}

void Car::SpawnSkidMark()
{
	Vector2 position = Utils::Vector2Add( mPosition, Utils::Vector2Scale(mDirection, -20));
	mSkidMarks.push_back( new SkidMark{ position, Utils::RotFromVector2(mDirection) + 90, GetTime() + mSkidMarkLifetime});
	position = Utils::Vector2Add(mPosition, Utils::Vector2Scale(mDirection, 18));
	mSkidMarks.push_back(new SkidMark{ position, Utils::RotFromVector2(mDirection) + 90, GetTime() + mSkidMarkLifetime });
}

void Car::UpdateSkidMarks()
{
	double currentTime = GetTime();
	for (size_t i = 0; i < mSkidMarks.size(); i++)
	{
		if (mSkidMarks[i] == nullptr)
		{
			continue;
		}

		if (mSkidMarks[i]->lifetime <= currentTime) 
		{
			mSkidMarks.erase(mSkidMarks.begin() + i);
		}
		else
		{
			break;
		}
	}
}

void Car::DrawSkidMarks() const
{
	double currentTime = GetTime();
	Rectangle skidMarkRect = { 0, 0, mSize.x, mSize.x * 0.21 };
	Texture* skidMarkTexture = AssetBank::GetInstance()->GetSkidMarkTexture();

	for (const SkidMark* skidMark : mSkidMarks)
	{
		if (skidMark == nullptr)
		{
			continue;
		}
		skidMarkRect.x = skidMark->position.x;
		skidMarkRect.y = skidMark->position.y;

		float opacity = Utils::Clamp((skidMark->lifetime - currentTime) / mSkidMarkLifetime, 0.0f, 1.0f);
		Color color = { 255, 255, 255, opacity * 255 };

		DrawTexturePro(*skidMarkTexture, { 0, 0, (float)skidMarkTexture->width, (float)skidMarkTexture->height }, skidMarkRect, { skidMarkRect.width * 0.5f, skidMarkRect.height * 0.5f }, skidMark->rotation, color);
	}

}

Car::Car() :
	mPosition{ 0,0 },
	mSize{ 0,0 },
	mVelocity{ 0,0 },
	mDirection{ 1,0 },
	mTurnSpeed{ 0 },
	mAccelRate{ 0 },
	mMaxFriction{ 0 },
	mMinFriction{ 0 },
	mMaxSpeed{ 0 },
	mNumber{ 0 },
	mControls{ 0,0,0,0 },
	mTrackPtr{ nullptr },
	mHasCheckpoint{ false },
	mLapCount{ 0 },
	mBestLapTime{ 0.0f },
	mCurrentLapStartTime{ 0.0f },
	mSkidMarkLifetime{ 0.0f }
{
}

Car::~Car()
{
}

Car::Car(Vector2 position, Vector2 size, Vector2 direction, Track* trackPtr, float turnSpeed, float accel, float maxSpeed, CarControls controls, int number) :
	mPosition{ position },
	mSize{ size },
	mVelocity{ 0,0 },
	mDirection{ direction },
	mTurnSpeed{ turnSpeed },
	mAccelRate{ accel },
	mMaxFriction{ 0.90f },
	mMinFriction{ 0.99f },
	mMaxSpeed{ maxSpeed },
	mNumber{ number },
	mControls{ controls },
	mTrackPtr{ trackPtr },
	mHasCheckpoint{ false },
	mLapCount{ 0 },
	mBestLapTime{ FLT_MAX },
	mCurrentLapStartTime{ 0.0f },
	mSkidMarkLifetime{ 15.0f }
{
}

void Car::Update() 
{
	Tilemap* tilemapPtr = mTrackPtr->GetTilemap();

	int row = (int)(mPosition.y / mTrackPtr->GetTilemap()->GetTileSize().y);
	int col = (int)(mPosition.x / mTrackPtr->GetTilemap()->GetTileSize().x);

	float tileTurnSpeed = 0;

	float angleDiff = Utils::Abs(Utils::DotProduct(Utils::Normalize(mDirection), Utils::Normalize(mVelocity)));

	float speed = Utils::Lenght(mVelocity);

	if (IsKeyDown(mControls.turnLeft))
	{
		tileTurnSpeed = (tilemapPtr->GetTile(row, col)->GetLayer1Index() != 0) ? mTurnSpeed : mTurnSpeed * 0.2f;
		mDirection = Utils::Vector2FromRot(Utils::RotFromVector2(mDirection) - Utils::Clamp(tileTurnSpeed * angleDiff * speed, 0, 200) * GetFrameTime());
	}
	if (IsKeyDown(mControls.turnRight))
	{
		tileTurnSpeed = (tilemapPtr->GetTile(row, col)->GetLayer1Index() != 0) ? mTurnSpeed : mTurnSpeed * 0.2f;
		mDirection = Utils::Vector2FromRot(Utils::RotFromVector2(mDirection) + Utils::Clamp(tileTurnSpeed * angleDiff * speed, 0, 200) * GetFrameTime());
	}

	if (IsKeyDown(mControls.accelerate)) 
	{
		mVelocity = Utils::Vector2Add(mVelocity, Utils::Vector2Scale(mDirection, mAccelRate * GetFrameTime()));
	}

	if (IsKeyDown(mControls.brake))
	{
		mVelocity = Utils::Vector2Add(mVelocity, Utils::Vector2Scale(mDirection, -mAccelRate * 0.5f * GetFrameTime()));
	}

	if (speed > 0)
	{
		float tileMaxFriction = (tilemapPtr->GetTile(row, col)->GetLayer1Index() != 0) ? mMaxFriction : 0.8f;
		float tileMinFriction = (tilemapPtr->GetTile(row, col)->GetLayer1Index() != 0) ? mMinFriction : 0.9f;

		float absAngleDiff = Utils::Abs(angleDiff);
		float dynamicFriction = Utils::Lerp(tileMaxFriction, tileMinFriction, absAngleDiff);

		if (IsKeyDown(mControls.brake))
		{
			float dynamicBraking = Utils::Lerp(0.999f, 0.9f, absAngleDiff);
			mVelocity = Utils::Vector2Scale(mVelocity, dynamicBraking);
		}

		mVelocity = Utils::Vector2Scale(mVelocity, dynamicFriction);

		if (speed > mMaxSpeed)
		{
			mVelocity = Utils::Vector2Scale(Utils::Normalize(mVelocity), mMaxSpeed);
		}

		if (absAngleDiff < 0.9f)
		{
			SpawnSkidMark();
		}

	}

	mPosition = Utils::Vector2Add(mPosition, Utils::Vector2Scale(mVelocity, GetFrameTime()));

	CheckCollisions();
	UpdateSkidMarks();
}

void Car::Draw() const
{
	Rectangle rect = { mPosition.x, mPosition.y, mSize.x, mSize.y };
	Texture* texture = AssetBank::GetInstance()->GetCarTexture(mNumber);
	DrawTexturePro(*texture, { 0, 0, (float)texture->width, (float)texture->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, Utils::RotFromVector2(mDirection) + 90, WHITE);

	Rectangle carRect = { mPosition.x, mPosition.y, mSize.x, mSize.y };
	float carRot = Utils::RotFromVector2(mDirection) + 90;

	float minDistance = Utils::Max(mSize.x, mSize.y) * 3;
	minDistance *= minDistance;

	// =================== Debug Collision Visualization ===================
	//for (const auto& obstacle : mTrackPtr->GetTrackObjects()->GetObstacles())
	//{
	//	float sqrDistance = Utils::SqrLenght(Utils::Vector2Substract({ mPosition.x, mPosition.y }, obstacle.GetPosition()));
	//	if (sqrDistance <= minDistance)
	//	{
	//		Rectangle obstacleRect = { obstacle.GetPosition().x, obstacle.GetPosition().y, obstacle.GetSize().x, obstacle.GetSize().y };
	//
	//		OBBCollision result = Utils::CheckOBB(carRect, carRot, obstacleRect, 0);
	//
	//		if (result.collision)
	//		{
	//			obstacleRect.x -= obstacleRect.width * 0.5f;
	//			obstacleRect.y -= obstacleRect.height * 0.5f;
	//			DrawRectangleRec(obstacleRect, { 255, 0, 0, 100 });
	//		}
	//	}
	//}
	// =======================================================================
}

Vector2 Car::GetPosition() const
{
	return mPosition;
}

Vector2 Car::GetSize() const
{
	return mSize;
}

Vector2 Car::GetDirection() const
{
	return mDirection;
}

bool Car::HasCheckpoint() const
{
	return mHasCheckpoint;
}

void Car::SetHasCheckpoint(bool hasCheckpoint)
{
	mHasCheckpoint = hasCheckpoint;
}

int Car::GetLapCount() const
{
	return mLapCount;
}

float Car::GetBestLapTime() const
{
	return mBestLapTime;
}

float Car::GetCurrentLapTime() const
{
	return GetTime() - mCurrentLapStartTime;
}

void Car::StartCurrentLap()
{
	mCurrentLapStartTime = GetTime();
}

void Car::FinishLap()
{
	mLapCount++;
	mHasCheckpoint = false;

	if (GetCurrentLapTime() < mBestLapTime)
	{
		mBestLapTime = GetCurrentLapTime();
	}

	StartCurrentLap();
}





