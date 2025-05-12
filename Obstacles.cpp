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
	int squarSide = Utils::Max(mSize.x, mSize.y);
	Rectangle rect{ mPosition.x - squarSide/2, mPosition.y - squarSide/2, squarSide, squarSide };
	Texture* text = AssetBank::GetInstance()->GetObstacleTexture();
	DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, mRotation, WHITE);

	rect = { mPosition.x - mSize.x *2, mPosition.y - mSize.y, mSize.x, mSize.y }; // need to debug
	DrawRectangleRec(rect, RED);
}

Vector2 Obstacles::GetPosition() const
{
	return mPosition;
}

Vector2 Obstacles::GetSize() const
{
	return mSize;
}
