#include "Engine.h"

Engine::Engine() :
	mTileCursor{ nullptr },
	mTrack{ nullptr },
	mCar{ nullptr },
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
	mCar = new Car({ 200, 200 }, { 50, 100 }, {1,0}, 50);
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

		mCar->Update();

		break;

	}

	

}

void Engine::Draw()
{
	Rectangle rect = { 0, 0, 0, 0 };
	Texture* text = nullptr;


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

		rect = { (float) GetScreenWidth() - 100, (float) GetScreenHeight() - 50, 200, 200};
		text = AssetBank::GetInstance()->GetEditorControlsTexture();
		DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, 0, WHITE);
		Utils::DrawTextCentered("Enter to change mode", { (float)GetScreenWidth() - 125, (float)GetScreenHeight() - 125 }, 20);

		if (mTileCursor->isTrackValid()) 
		{
			Utils::DrawTextCentered("S to Save", { (float)GetScreenWidth() - 125, (float)GetScreenHeight() - 150 }, 20);
		}
		else
		{
			Utils::DrawTextCentered("Track invalid", { (float)GetScreenWidth() - 125, (float)GetScreenHeight() - 150 }, 20);
		}

		break;

	case RaceState:
		mTrack->Draw();
		mCar->Draw();
		break;

	}
	
}
