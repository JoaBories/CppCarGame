#pragma once
#include <string>
#include "Tilemap.h"
#include "TileCursor.h"
#include "TrackObjects.h"

enum GameState
{
	Edit,
	Play,
};


class Engine
{
private :
	Tilemap mTilemap;
	TileCursor mTileCursor;
	TrackObjects mTrackObjects;

public :
	Engine();
	~Engine();

	void Init();
	void Update();
	void Draw();
};

