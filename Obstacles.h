#pragma once
#include "raylib.h"

class Obstacles
{
private:
	Vector2 mPosition;
	Vector2 mSize;
	int mRotation;

public:
	Obstacles();
	~Obstacles();
	Obstacles(Vector2 position, Vector2 size, int rotation);

	void Draw() const;

	Vector2 GetPosition() const;
	Vector2 GetSize() const;
	int GetRotation() const;

};

