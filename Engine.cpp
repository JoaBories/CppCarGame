#include "Engine.h"

Engine::Engine() :
	mTileCursor{ nullptr },
	mTrack{ nullptr },
	mGameState{ StartState }
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
	switch (mGameState)
	{
	case StartState:
		if (IsKeyPressed(KEY_E))
		{
			mGameState = EditorState;
			mTrack->LoadTrack();
		}

		else if (IsKeyPressed(KEY_P) && mTrack->IsThereASave())
		{
			mGameState = RaceState;
			mTrack->LoadTrack();
		}
		break;

	case EditorState:
		mTileCursor->Update();
		if (mTileCursor->HasSaved())
		{
			mGameState = StartState;
			mTileCursor->Reset();
		}
		break;

	case RaceState:

		break;

	}

	

}

void Engine::Draw()
{
	switch (mGameState)
	{
	case StartState:
		Utils::DrawTextCentered("Mini Car Race", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 3 }, 20);
		
		if (mTrack->IsThereASave())
		{
			Utils::DrawTextCentered("Play - P", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 }, 20);
		}
		
		Utils::DrawTextCentered("Track Editor - E", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 3 * 2 }, 20);
		break;

	case EditorState:
		mTrack->Draw();
		mTileCursor->Draw();
		break;

	case RaceState:
		mTrack->Draw();
		break;

	}
	
}
