#include "TileCursor.h"

TileCursor::TileCursor() :
	mRowIndex{ 0 },
	mColIndex{ 0 },
	mRowMax{ 0 },
	mColMax{ 0 },
	mRotation{ 0 },
	mSize{ 0, 0 },
	mType{ SetTiles },
	mTilemap{ nullptr },
	mTrackObjects{ nullptr },
	mTileTexture{ nullptr }
{
}

TileCursor::~TileCursor()
{
}

TileCursor::TileCursor(int maxRow, int maxCol, Vector2 size, Tilemap* mTilemap, TrackObjects* trackObjects) :
	mRowIndex{ 0 },
	mColIndex{ 0 },
	mRowMax{ maxRow },
	mColMax{ maxCol },
	mRotation{ 0 },
	mSize{ size },
	mType{ SetTiles },
	mTilemap{ mTilemap },
	mTrackObjects{ trackObjects },
	mTileTexture{ nullptr }
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

	Vector2 CheckpointDir = { 0,0 };
	Vector2 CheckpointSize = { 0,0 };
	Vector2 ObstacleSize = { 0,0 };

	switch (mRotation)
	{
	case 0:
		CheckpointDir = { 1, 0 };
		CheckpointSize = { mSize.x, mSize.y * 3 };
		ObstacleSize = { mSize.x / 3, mSize.y };
		break;

	case 90:
		CheckpointDir = { 0, 1 };
		CheckpointSize = { mSize.x * 3, mSize.y };
		ObstacleSize = { mSize.x, mSize.y / 3 };
		break;

	case 180:
		CheckpointDir = { -1, 0 };
		CheckpointSize = { mSize.x, mSize.y * 3 };
		ObstacleSize = { mSize.x / 3, mSize.y };
		break;

	case 270:
		CheckpointDir = { 0, -1 };
		CheckpointSize = { mSize.x * 3, mSize.y };
		ObstacleSize = { mSize.x, mSize.y / 3 };
		break;
	}

	switch (mType)
	{
	case SetTiles:
		if (IsKeyPressed(KEY_E))
		{
			int index = mTilemap->GetTile(mRowIndex, mColIndex)->GetLayer1Index();
			index++;

			if (index == 10)
			{
				index = 0;
			}

			mTilemap->GetTile(mRowIndex, mColIndex)->SetLayer1Index(index);
		}

		if (IsKeyPressed(KEY_R))
		{
			int rot = mTilemap->GetTile(mRowIndex, mColIndex)->GetLayer1Rot();
			rot += 90;

			if (rot == 360)
			{
				rot = 0;
			}

			mTilemap->GetTile(mRowIndex, mColIndex)->SetLayer1Rot(rot);
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
			mTrackObjects->SetStart({ mSize.x * (1 + mColIndex), mSize.y * (1 + mRowIndex) }, CheckpointSize, CheckpointDir, mRotation);
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
			mTrackObjects->SetCheckpoint({ mSize.x * (1 + mColIndex), mSize.y * (1 + mRowIndex) }, CheckpointSize, CheckpointDir, mRotation);
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
			mTrackObjects->AddObstacle(Obstacles({ mSize.x * (1 + mColIndex), mSize.y * (1 + mRowIndex) }, ObstacleSize, mRotation));
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
			if (mTrackObjects->GetStart().position.x == 0 && mTrackObjects->GetStart().position.y == 0)
			{
				mTrackObjects->SetStart({ mSize.x * (1 + mColIndex), mSize.y * (1 + mRowIndex) }, CheckpointSize, CheckpointDir, mRotation);
			}
			mRotation = 0;
			break;

		case SetCheckpoint:
			mType = SetObstacles;
			if (mTrackObjects->GetCheckpoint().position.x == 0 && mTrackObjects->GetCheckpoint().position.y == 0)
			{
				mTrackObjects->SetCheckpoint({ mSize.x * (1 + mColIndex), mSize.y * (1 + mRowIndex) }, CheckpointSize, CheckpointDir, mRotation);
			}
			mRotation = 0;
			break;

		case SetObstacles:
			mType = SetTiles;
			mRotation = 0;
			//change engine type
			break;
		}
	}
}

void TileCursor::Draw() const
{
	Rectangle rect = { 0, 0, 0, 0 };
	Texture* text = nullptr;

	Checkpoint start = mTrackObjects->GetStart();
	if (start.position.x != 0 || start.position.y != 0)
	{
		rect = { start.position.x - mSize.x / 2, start.position.y - mSize.y / 2, mSize.x, mSize.y * 3 };
		text = AssetBank::GetInstance()->GetStartTexture();
		DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, start.Rotation, WHITE);
	}

	Checkpoint checkpoint = mTrackObjects->GetCheckpoint();
	if (checkpoint.position.x != 0 || checkpoint.position.y != 0)
	{
		rect = { checkpoint.position.x - mSize.x / 2, checkpoint.position.y - mSize.y / 2, mSize.x, mSize.y * 3 };
		text = AssetBank::GetInstance()->GetCheckpointTexture();
		DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, checkpoint.Rotation, WHITE);
	}


	Vector2 pos = { mSize.x * (1 + mColIndex), mSize.y * (1 + mRowIndex) };
	rect = { pos.x - mSize.x / 2, pos.y - mSize.y / 2, mSize.x, mSize.y };
	text = mTileTexture;

	switch (mType)
	{
	case SetTiles:


		break;

	case SetStart:
		text = AssetBank::GetInstance()->GetStartTexture();
		rect = { pos.x - mSize.x / 2, pos.y - mSize.y / 2, mSize.x, mSize.y*3 };
		break;

	case SetCheckpoint:
		text = AssetBank::GetInstance()->GetCheckpointTexture();
		rect = { pos.x - mSize.x / 2, pos.y - mSize.y / 2, mSize.x, mSize.y*3 };
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
