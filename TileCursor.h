#pragma once
#include "raylib.h"
#include "Tilemap.h"

enum CursorType
{
	Tiles,
	Start,
	Checkpoint,
	Obstacle
};


class TileCursor
{
private:
	int mRowIndex;
	int mColIndex;
	int mRowMax;
	int mColMax;
	Vector2 mSize;
	CursorType mType;
	Tilemap* mTilemap;
	Texture *mTileTexture;
	Texture *mStartTexture;
	Texture *mCheckpointTexture;
	Texture *mObstacleTexture;

public:
	TileCursor();
	~TileCursor();
	TileCursor(int maxRow, int maxCol, Vector2 size, Tilemap* mTilemap);

	void Update();
	void Draw() const;

	int GetRowIndex() const;
	int GetColIndex() const;
};

