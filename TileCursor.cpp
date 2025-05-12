#include "TileCursor.h"

bool TileCursor::isTrackValid() const
{
	if (mTrack->GetTrackObjects()->GetStart().position.x != 0 || mTrack->GetTrackObjects()->GetStart().position.y != 0) 
	{
		if (mTrack->GetTrackObjects()->GetCheckpoint().position.x != 0 || mTrack->GetTrackObjects()->GetCheckpoint().position.y != 0)
		{
			return true;
		}
	}

	return false;
}

TileCursor::TileCursor() :
	mRowIndex{ 0 },
	mColIndex{ 0 },
	mRowMax{ 0 },
	mColMax{ 0 },
	mRotation{ 0 },
	mSize{ 0, 0 },
	mType{ SetTiles },
	mTrack{ nullptr },
	mTileTexture{ nullptr },
	hasSaved{ false }
{
}

TileCursor::~TileCursor()
{
}

TileCursor::TileCursor(int maxRow, int maxCol, Vector2 size, Track* track) :
	mRowIndex{ 0 },
	mColIndex{ 0 },
	mRowMax{ maxRow },
	mColMax{ maxCol },
	mRotation{ 0 },
	mSize{ size },
	mType{ SetTiles },
	mTrack{ track },
	mTileTexture{ nullptr },
	hasSaved{ false }
{
	Image img = LoadImage("resources/img/cursor.png");
	mTileTexture = new Texture(LoadTextureFromImage(img));
	UnloadImage(img);
}

void TileCursor::Update()
{
	if (IsKeyPressed(KEY_UP) && mRowIndex > 0)
	{
		mRowIndex--;
	}
	if (IsKeyPressed(KEY_DOWN) && mRowIndex < mRowMax - 1)
	{
		mRowIndex++;
	}
	if (IsKeyPressed(KEY_LEFT) && mColIndex > 0)
	{
		mColIndex--;
	}
	if (IsKeyPressed(KEY_RIGHT) && mColIndex < mColMax - 1)
	{
		mColIndex++;
	}

	if (IsKeyPressed(KEY_S) && isTrackValid())
	{
		mTrack->SaveTrack();
		hasSaved = true;
	}

	Vector2 CheckpointDir = { 0,0 };
	Vector2 CheckpointSize = { 0,0 };
	Vector2 ObstacleSize = { 0,0 };

	switch (mRotation)
	{
	case 0:
		CheckpointDir = { 1, 0 };
		CheckpointSize = { mSize.x, mSize.y * 3 };
		ObstacleSize = { mSize.x/2.5f, mSize.y };
		break;

	case 90:
		CheckpointDir = { 0, 1 };
		CheckpointSize = { mSize.x * 3, mSize.y };
		ObstacleSize = { mSize.x, mSize.y/2.5f };
		break;

	case 180:
		CheckpointDir = { -1, 0 };
		CheckpointSize = { mSize.x, mSize.y * 3 };
		ObstacleSize = { mSize.x/2.5f, mSize.y };
		break;

	case 270:
		CheckpointDir = { 0, -1 };
		CheckpointSize = { mSize.x * 3, mSize.y };
		ObstacleSize = { mSize.x, mSize.y/2.5f };
		break;
	}

	switch (mType)
	{
	case SetTiles:
		if (IsKeyPressed(KEY_E))
		{
			int index = mTrack->GetTilemap()->GetTile(mRowIndex, mColIndex)->GetLayer1Index();
			index++;

			if (index == 10)
			{
				index = 0;
			}

			mTrack->GetTilemap()->GetTile(mRowIndex, mColIndex)->SetLayer1Index(index);
		}

		if (IsKeyPressed(KEY_R))
		{
			int rot = mTrack->GetTilemap()->GetTile(mRowIndex, mColIndex)->GetLayer1Rot();
			rot += 90;

			if (rot == 360)
			{
				rot = 0;
			}

			mTrack->GetTilemap()->GetTile(mRowIndex, mColIndex)->SetLayer1Rot(rot);
		}
		break;

	case SetStart:
		if (IsKeyPressed(KEY_R))
		{
			mRotation += 90;

			if (mRotation == 360)
			{
				mRotation = 0;
			}
		}

		if (IsKeyPressed(KEY_E))
		{
			mTrack->GetTrackObjects()->SetStart({ mSize.x * (0.5f + mColIndex), mSize.y * (0.5f + mRowIndex) }, CheckpointSize, CheckpointDir, mRotation);
		}

		break;

	case SetCheckpoint:
		if (IsKeyPressed(KEY_R))
		{
			mRotation += 90;

			if (mRotation == 360)
			{
				mRotation = 0;
			}
		}

		if (IsKeyPressed(KEY_E))
		{
			mTrack->GetTrackObjects()->SetCheckpoint({ mSize.x * (0.5f + mColIndex), mSize.y * (0.5f + mRowIndex) }, CheckpointSize, CheckpointDir, mRotation);
		}

		break;

	case SetObstacles:
		if (IsKeyPressed(KEY_R))
		{
			mRotation += 90;

			if (mRotation == 360)
			{
				mRotation = 0;
			}
		}

		if (IsKeyPressed(KEY_E))
		{
			bool isSamePos = false;
			int index = 0;
			vector<Obstacles> obstacles = mTrack->GetTrackObjects()->GetObstacles();
			for (int i = 0; i < obstacles.size(); i++)
			{
				Obstacles obstacle = obstacles[i];

				if ( obstacle.GetPosition().x == mSize.x * (0.5f + mColIndex) && obstacle.GetPosition().y == mSize.y * (0.5f + mRowIndex))
				{
					isSamePos = true;
					index = i;
				}
			}

			if (!isSamePos)
			{
				mTrack->GetTrackObjects()->AddObstacle(Obstacles({ mSize.x * (0.5f + mColIndex), mSize.y * (0.5f + mRowIndex) }, ObstacleSize, mRotation));
			}
			else
			{
				mTrack->GetTrackObjects()->RemoveObstacle(index);
			}
		}

		break;

	}

	if (IsKeyPressed(KEY_ENTER))
	{
		switch (mType)
		{
		case SetTiles:
			mType = SetStart;
			mRotation = 0;
			break;

		case SetStart:
			mType = SetCheckpoint;
			if (mTrack->GetTrackObjects()->GetStart().position.x == 0 && mTrack->GetTrackObjects()->GetStart().position.y == 0)
			{
				mTrack->GetTrackObjects()->SetStart({ mSize.x * (0.5f + mColIndex), mSize.y * (0.5f + mRowIndex) }, CheckpointSize, CheckpointDir, mRotation);
			}
			mRotation = 0;
			break;

		case SetCheckpoint:
			mType = SetObstacles;
			if (mTrack->GetTrackObjects()->GetCheckpoint().position.x == 0 && mTrack->GetTrackObjects()->GetCheckpoint().position.y == 0)
			{
				mTrack->GetTrackObjects()->SetCheckpoint({ mSize.x * (0.5f + mColIndex), mSize.y * (0.5f + mRowIndex) }, CheckpointSize, CheckpointDir, mRotation);
			}
			mRotation = 0;
			break;

		case SetObstacles:
			mType = SetTiles;
			mRotation = 0;
			break;
		}
	}
}

void TileCursor::Draw() const
{
	Rectangle rect = { 0, 0, 0, 0 };
	Texture* text = nullptr;

	//start line
	Checkpoint start = mTrack->GetTrackObjects()->GetStart();
	if (start.position.x != 0 || start.position.y != 0)
	{
		rect = { start.position.x, start.position.y, mSize.x, mSize.y * 3 };
		text = AssetBank::GetInstance()->GetStartTexture();
		DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, start.Rotation, WHITE);
	}

	//checkpoint
	Checkpoint checkpoint = mTrack->GetTrackObjects()->GetCheckpoint();
	if (checkpoint.position.x != 0 || checkpoint.position.y != 0)
	{
		rect = { checkpoint.position.x, checkpoint.position.y, mSize.x, mSize.y * 3 };
		text = AssetBank::GetInstance()->GetCheckpointTexture();
		DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, checkpoint.Rotation, WHITE);
	}

	//Cursor
	Vector2 pos = { mSize.x * (0.5 + mColIndex), mSize.y * (0.5 + mRowIndex) };
	rect = { pos.x, pos.y, mSize.x, mSize.y };
	text = mTileTexture;

	switch (mType)
	{
	case SetTiles:
		break;

	case SetStart:
		text = AssetBank::GetInstance()->GetStartTexture();
		rect = { pos.x, pos.y, mSize.x, mSize.y*3 };
		break;

	case SetCheckpoint:
		text = AssetBank::GetInstance()->GetCheckpointTexture();
		rect = { pos.x, pos.y, mSize.x, mSize.y*3 };
		break;

	case SetObstacles:
		text = AssetBank::GetInstance()->GetObstacleTexture();

		break;
	}

	DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, mRotation, WHITE);
}

int TileCursor::GetRowIndex() const
{
	return mRowIndex;
}

int TileCursor::GetColIndex() const
{
	return mColIndex;
}

void TileCursor::Reset()
{
	mRowIndex = 0;
	mColIndex = 0;
	mRotation = 0;
	mType = SetTiles;
	hasSaved = false;
}
