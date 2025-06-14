#include "Engine.h"

void Engine::StartRace()
{
	mGameState = RaceState;
	mTrack->LoadTrack();

	Vector2 carSize = { 30, 60 };
	Vector2 startDir = mTrack->GetTrackObjects()->GetStart().direction;

	Vector2 startPos = Utils::Vector2Add(mTrack->GetTrackObjects()->GetStart().position, {0, carSize.y * 0.5f});
	CarControls controls = { KEY_D, KEY_A, KEY_W, KEY_S };
	mCar1 = new Car(startPos, carSize, startDir , mTrack, 5, 500, 500, controls, 1);

	startPos = Utils::Vector2Substract(mTrack->GetTrackObjects()->GetStart().position, { 0, carSize.y * 0.5f});
	controls = { KEY_RIGHT, KEY_LEFT, KEY_UP, KEY_DOWN };
	mCar2 = new Car(startPos, carSize, startDir , mTrack, 5, 500, 500, controls, 2);

	mCar1->StartCurrentLap();
	mCar2->StartCurrentLap();
}

void Engine::UpdateCarLap(Car* car)
{
	Rectangle carRect = { car->GetPosition().x, car->GetPosition().y, car->GetSize().x, car->GetSize().y };
	float carRot = Utils::RotFromVector2(car->GetDirection()) + 90;

	if (!car->HasCheckpoint())
	{
		Rectangle checkpointRect = { mTrack->GetTrackObjects()->GetCheckpoint().position.x,mTrack->GetTrackObjects()->GetCheckpoint().position.y,mTrack->GetTrackObjects()->GetCheckpoint().size.x,mTrack->GetTrackObjects()->GetCheckpoint().size.y };

		if (Utils::CheckOBB(carRect, carRot, checkpointRect, 0).collision)
		{
			car->SetHasCheckpoint(true);
		}
	}
	else
	{
		Rectangle checkpointRect = { mTrack->GetTrackObjects()->GetStart().position.x,mTrack->GetTrackObjects()->GetStart().position.y,mTrack->GetTrackObjects()->GetStart().size.x,mTrack->GetTrackObjects()->GetStart().size.y };
		if (Utils::CheckOBB(carRect, carRot, checkpointRect, 0).collision)
		{
			car->FinishLap();
		}
	}
}

void Engine::DrawCarLap(Car* car, Vector2 centerPos, Color textColor, Color backgroundColor)
{
	Utils::DrawTextWithBackground("Lap: " + std::to_string(car->GetLapCount()), Utils::Vector2Substract(centerPos, { 0, 60 }), 40, textColor, backgroundColor, 10);

	if (car->GetLapCount() != 0)
	{
		string lapTimeText = std::to_string(car->GetCurrentLapTime()).substr(0, 4);
		Utils::DrawTextWithBackground(lapTimeText + " s", centerPos, 40, textColor, backgroundColor, 10);
		lapTimeText = std::to_string(car->GetBestLapTime()).substr(0, 4);
		Utils::DrawTextWithBackground(lapTimeText + " s", Utils::Vector2Add(centerPos, { 0, 60}), 40, textColor, backgroundColor, 10);
	}
	else
	{
		string lapTimeText = std::to_string(car->GetCurrentLapTime()).substr(0, 4);
		Utils::DrawTextWithBackground(lapTimeText + " s", centerPos, 40, textColor, backgroundColor, 10);
	}
}

Engine::Engine() :
	mTileCursor{ nullptr },
	mTrack{ nullptr },
	mCar1{ nullptr },
	mCar2{ nullptr },
	mGameState{ StartState },
	mOrange{ 245, 155, 20, 255 }
{
}

Engine::~Engine()
{
	delete mTileCursor;
	delete mTrack;
	delete mCar1;
	delete mCar2;
}

void Engine::Init()
{
	mTrack = new Track();
	mTileCursor = new TileCursor(9, 16, mTrack->GetTilemap()->GetTileSize(), mTrack);

	mCar1 = nullptr;
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

		mCar1->Update();
		mCar2->Update();

		UpdateCarLap(mCar1);
		UpdateCarLap(mCar2);

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

		mCar1->DrawSkidMarks();
		mCar2->DrawSkidMarks();

		mCar1->Draw();
		mCar2->Draw();

		DrawCarLap(mCar1, { (float)GetScreenWidth() * 0.05f, (float)GetScreenHeight() *0.125f}, mOrange, {0, 0, 0, 100});

		Color tempColor = mOrange;
		tempColor.a = 100;
		DrawCarLap(mCar2, { (float)GetScreenWidth() * 0.95f, (float)GetScreenHeight() *0.125f}, { 50, 50, 50, 255 }, tempColor);
		
		
		break;

	}
	
}
