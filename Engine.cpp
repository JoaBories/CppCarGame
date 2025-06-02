#include "Engine.h"

void Engine::StartRace()
{
	mGameState = RaceState;
	mTrack->LoadTrack();

	CarControls controls = { KEY_D, KEY_A, KEY_W, KEY_S };
	mCar = new Car(mTrack->GetTrackObjects()->GetStart().position, {30,60}, mTrack->GetTrackObjects()->GetStart().direction, mTrack, 5, 500, 500, controls);

	mCar->StartCurrentLap();
}

Engine::Engine() :
	mTileCursor{ nullptr },
	mTrack{ nullptr },
	mCar{ nullptr },
	mGameState{ StartState },
	mOrange{ 245, 155, 20, 255 }
{
}

Engine::~Engine()
{
}

void Engine::Init()
{
	mTrack = new Track();
	mTileCursor = new TileCursor(9, 16, mTrack->GetTilemap()->GetTileSize(), mTrack);

	mCar = nullptr;
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
			StartRace();
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

		Rectangle carRect = { mCar->GetPosition().x, mCar->GetPosition().y, mCar->GetSize().x, mCar->GetSize().y };
		float carRot = Utils::RotFromVector2(mCar->GetDirection()) + 90;

		if (!mCar->HasCheckpoint())
		{
			Rectangle checkpointRect = {mTrack->GetTrackObjects()->GetCheckpoint().position.x,mTrack->GetTrackObjects()->GetCheckpoint().position.y,mTrack->GetTrackObjects()->GetCheckpoint().size.x,mTrack->GetTrackObjects()->GetCheckpoint().size.y };
			
			if (Utils::CheckOBB(carRect, carRot, checkpointRect, 0).collision)
			{
				mCar->SetHasCheckpoint(true);
			}
		}
		else
		{
			Rectangle checkpointRect = { mTrack->GetTrackObjects()->GetStart().position.x,mTrack->GetTrackObjects()->GetStart().position.y,mTrack->GetTrackObjects()->GetStart().size.x,mTrack->GetTrackObjects()->GetStart().size.y };
			if (Utils::CheckOBB(carRect, carRot, checkpointRect, 0).collision)
			{
				mCar->FinishLap();
			}
		}

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
		Utils::DrawTextCentered("Mini Car Race", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 3 }, 20, mOrange);
		
		if (mTrack->IsThereASave())
		{
			Utils::DrawTextCentered("Play - P", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 }, 20, mOrange);
		}
		
		Utils::DrawTextCentered("Track Editor - E", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 3 * 2 }, 20, mOrange);
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

		Utils::DrawRectangleCentered({ (float)GetScreenWidth() - 100, 50, 175, 75 }, {0,0,0,100} );
		Utils::DrawTextCentered("Lap: " + std::to_string(mCar->GetLapCount()), { (float)GetScreenWidth() - 100, 50 }, 40, mOrange);
		
		if (mCar->GetLapCount() != 0)
		{
			Utils::DrawRectangleCentered({ 100, 62.5f, 175, 100 }, { 0,0,0,100 });
			string lapTimeText = std::to_string(mCar->GetCurrentLapTime()).substr(0, 4);
			Utils::DrawTextCentered(lapTimeText + " s", { 100, 50 }, 50, mOrange);
			lapTimeText = std::to_string(mCar->GetBestLapTime()).substr(0, 4);
			Utils::DrawTextCentered(lapTimeText + " s", { 100, 95 }, 30, mOrange);
		}
		else
		{
			Utils::DrawRectangleCentered({ 100, 50, 175, 75 }, { 0,0,0,100 });
			string lapTimeText = std::to_string(mCar->GetCurrentLapTime()).substr(0, 4);
			Utils::DrawTextCentered(lapTimeText + " s", { 100, 50 }, 50, mOrange);
		}

		
		
		break;

	}
	
}
