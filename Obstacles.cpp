#include "Obstacles.h"

Obstacles::Obstacles() :
	mPosition{ 0, 0 },
	mSize{ 0, 0 }
{
}

Obstacles::~Obstacles()
{
}

Obstacles::Obstacles(Vector2 position, Vector2 size) :
	mPosition{ position },
	mSize{ size }
{
}

void Obstacles::Draw() const
{
	// draw the obstacle
}

Vector2 Obstacles::GetPosition() const
{
	return mPosition;
}

Vector2 Obstacles::GetSize() const
{
	return mSize;
}
