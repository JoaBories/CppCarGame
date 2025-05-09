#pragma once
#include <string>
#include "Tilemap.h"

class Engine
{
private :
	Tilemap mTilemap;

public :
	Engine();
	~Engine();

	void Init();
	void Update();
	void Draw();
};

