#include "Engine.h"

Engine::Engine() :
	mTileCursor{ nullptr },
	mTrack{ nullptr }
{
}

Engine::~Engine()
{
}

void Engine::Init()
{
	mTrack = new Track();
	mTileCursor = new TileCursor(9, 16, mTrack->GetTilemap()->GetTileSize(), mTrack);
}

void Engine::Update()
{
	mTileCursor->Update();

}

void Engine::Draw()
{
	mTrack->Draw();
	mTileCursor->Draw();
}
