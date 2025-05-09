#include "Engine.h"

Engine::Engine() :
	mTilemap{Tilemap()}
{
}

Engine::~Engine()
{
}

void Engine::Init()
{
	mTilemap = Tilemap(9, 16);
}

void Engine::Update()
{
}

void Engine::Draw()
{
	mTilemap.Draw();	
}
