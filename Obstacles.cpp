#include "Obstacles.h"
#include "Utils.h"
#include "AssetBank.h"

Obstacles::Obstacles() :
	mPosition{ 0, 0 },
	mSize{ 0, 0 },
	mRotation{ 0 }
{
}

Obstacles::~Obstacles()
{
}

Obstacles::Obstacles(Vector2 position, Vector2 size, int rotation) :
	mPosition{ position },
	mSize{ size },
	mRotation{ rotation }
{
}

void Obstacles::Draw() const
{
	int squareSide = Utils::Max(mSize.x, mSize.y);
	Rectangle rect1{ mPosition.x, mPosition.y, squareSide, squareSide };
	Texture* text = AssetBank::GetInstance()->GetObstacleTexture();
	DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect1, { rect1.width * 0.5f, rect1.height * 0.5f }, mRotation, WHITE);
}

Vector2 Obstacles::GetPosition() const
{
	return mPosition;
}

Vector2 Obstacles::GetSize() const
{
	return mSize;
}

int Obstacles::GetRotation() const
{
	return mRotation;
}
