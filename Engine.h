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
	Car* mCar1;
	Car* mCar2;

	GameState mGameState;

	Color mOrange;

	void StartRace();

	void UpdateCarLap(Car* car);
	void DrawCarLap(Car* car, Vector2 centerPos, Color textColor, Color backgroundColor);

public :
	Engine();
	~Engine();

	void Init();
	void Update();
	void Draw();
};

