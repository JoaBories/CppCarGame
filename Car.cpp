#include "Car.h"

Car::Car() :
	mPosition{ 0,0 },
	mSize{ 0,0 },
	mVelocity{ 0,0 },
	mDirection{ 1,0 },
	mTurnSpeed{ 0 }
{
}

Car::~Car()
{
}

Car::Car(Vector2 position, Vector2 size, Vector2 direction, float turnSpeed) :
	mPosition{ position },
	mSize{ size },
	mVelocity{ 0,0 },
	mDirection{ direction },
	mTurnSpeed{ turnSpeed }
{

}



void Car::Update() 
{
	if (IsKeyUp(KEY_LEFT))
	{
		mDirection = Utils::Vector2FromRot(Utils::RotFromVector2(mDirection) + mTurnSpeed * GetFrameTime() * Utils::Lenght(mVelocity));
	}
	if (IsKeyUp(KEY_RIGHT))
	{
		mDirection = Utils::Vector2FromRot(Utils::RotFromVector2(mDirection) - mTurnSpeed * GetFrameTime() * Utils::Lenght(mVelocity));
	}
}

void Car::Draw() const
{
	Rectangle rect = { mPosition.x, mPosition.y, mSize.x, mSize.y };
	Texture* texture = AssetBank::GetInstance()->GetCarTexture();
	DrawTexturePro(*texture, { 0, 0, (float)texture->width, (float)texture->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, Utils::RotFromVector2(mDirection) + 90, WHITE);
	DrawRectanglePro(rect, { rect.width * 0.5f, rect.height * 0.5f }, Utils::RotFromVector2(mDirection) + 90, { 255, 0, 0, 50 });
}