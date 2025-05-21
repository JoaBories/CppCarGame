#pragma once
#include "Track.h"

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

	Track* mTrack;

	Texture *mTileTexture;

	bool hasSaved;


public:
	TileCursor();
	~TileCursor();
	TileCursor(int maxRow, int maxCol, Vector2 size, Track* track);

	void Update();
	void Draw() const;

	int GetRowIndex() const;
	int GetColIndex() const;

	bool isTrackValid() const;
	bool HasSaved() const;
	void Reset();
};

