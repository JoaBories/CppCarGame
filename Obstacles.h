#pragma once
#include "raylib.h"

class Obstacles
{
private:
	Vector2 mPosition;
	Vector2 mSize;

public:
	Obstacles();
	~Obstacles();
	Obstacles(Vector2 position, Vector2 size);

	void Draw() const;

	Vector2 GetPosition() const;
	Vector2 GetSize() const;

};

