#pragma once
#include <raylib.h>
#include "AssetBank.h"

class Tile
{
private :
	void DrawLayer(Rectangle rect, TileLayer layer) const;

public :
	TileLayer mLayer0; // 0,1,0 -> grass
	TileLayer mLayer1; // 1,i,r -> sand with an index and a rotation

	Tile();
	~Tile();

	void DrawLayer0(Vector2 position, Vector2 size) const;
	void DrawLayer1(Vector2 position, Vector2 size) const;

	int GetLayer1Index() const;
	int GetLayer1Rot() const;

	void SetLayer1Index(int i);
	void SetLayer1Rot(int rot);
};

