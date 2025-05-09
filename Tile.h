#pragma once
#include <raylib.h>
#include "AssetBank.h"

enum SurfacingType
{
	Grass,
	Road,
	Sand,
};

class Tile
{
private :
	SurfacingType mSurfacingType;
	TileLayer mLayer0; // 0,1,0 -> grass
	TileLayer mLayer1; // 1,i,r -> sand with an index and a rotation
	TileLayer mLayer2; // 2,i,r -> road with an index and a rotation

	void DrawLayer(Rectangle rect, TileLayer layer) const;

public :
	Tile();
	~Tile();
	Tile(SurfacingType surface, TileLayer l0, TileLayer l1, TileLayer l2);

	void Draw(Vector2 position, Vector2 size) const;
};

