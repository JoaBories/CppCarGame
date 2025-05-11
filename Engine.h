#pragma once
#include <string>
#include "Tilemap.h"
#include "TileCursor.h"

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

public :
	Engine();
	~Engine();

	void Init();
	void Update();
	void Draw();
};

