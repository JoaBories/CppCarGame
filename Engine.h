#pragma once
#include <string>
#include "Track.h"
#include "TileCursor.h"

enum GameState
{
	StartState,
	EditorState,
	RaceState
};

class Engine
{
private :
	TileCursor* mTileCursor;
	Track* mTrack;
	GameState mGameState;

public :
	Engine();
	~Engine();

	void Init();
	void Update();
	void Draw();
};

