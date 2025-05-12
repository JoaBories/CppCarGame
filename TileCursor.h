#pragma once
#include "raylib.h"
#include "Tilemap.h"
#include "TrackObjects.h"

enum CursorType
{
	SetTiles,
	SetStart,
	SetCheckpoint,
	SetObstacles
};


class TileCursor
{
private:
	int mRowIndex;
	int mColIndex;
	int mRowMax;
	int mColMax;
	int mRotation;
	Vector2 mSize;

	CursorType mType;

	Tilemap* mTilemap;
	TrackObjects* mTrackObjects;

	Texture *mTileTexture;

public:
	TileCursor();
	~TileCursor();
	TileCursor(int maxRow, int maxCol, Vector2 size, Tilemap* tilemap, TrackObjects* trackObjects);

	void Update();
	void Draw() const;

	int GetRowIndex() const;
	int GetColIndex() const;
};

