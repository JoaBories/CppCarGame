#pragma once
#include <string>
#include "Track.h"
#include "TileCursor.h"

class Engine
{
private :
	TileCursor* mTileCursor;
	Track* mTrack;

public :
	Engine();
	~Engine();

	void Init();
	void Update();
	void Draw();
};

