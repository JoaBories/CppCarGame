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
	Car* mCar2;

	GameState mGameState;

	Color mOrange;

	void StartRace();

public :
	Engine();
	~Engine();

	void Init();
	void Update();
	void Draw();
};

