#pragma once
#include <string>
#include "Track.h"
#include "TileCursor.h"
#include "Car.h"

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
	Car* mCar;

	GameState mGameState;

public :
	Engine();
	~Engine();

	void Init();
	void Update();
	void Draw();
};

