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
	mTileTexture{ nullptr },
	mStartTexture{ nullptr },
	mCheckpointTexture{ nullptr },
	mObstacleTexture{ nullptr }
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
	mTileTexture{ nullptr },
	mStartTexture{ nullptr },
	mCheckpointTexture{ nullptr },
	mObstacleTexture{ nullptr }
{
	Image img = LoadImage("resources/img/cursor.png");
	mTileTexture = new Texture(LoadTextureFromImage(img));
	UnloadImage(img);

	img = LoadImage("resources/img/start.png");
	mStartTexture = new Texture(LoadTextureFromImage(img));
	UnloadImage(img);

	img = LoadImage("resources/img/checkpoint.png");
	mCheckpointTexture = new Texture(LoadTextureFromImage(img));
	UnloadImage(img);

	img = LoadImage("resources/img/cursor.png");
	mObstacleTexture = new Texture(LoadTextureFromImage(img));
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

		break;

	case SetObstacles:
		break;

	}

	if (IsKeyPressed(KEY_ENTER))
	{
		Vector2 Dir = { 0,0 };
		Vector2 Size = { 0,0 };

		switch (mRotation)
		{
		case 0:
			Dir = { 1, 0 };
			Size = { mSize.x, mSize.y * 3 };
			break;

		case 90:
			Dir = { 0, 1 };
			Size = { mSize.x * 3, mSize.y };
			break;

		case 180:
			Dir = { -1, 0 };
			Size = { mSize.x, mSize.y * 3 };
			break;

		case 270:
			Dir = { 0, -1 };
			Size = { mSize.x * 3, mSize.y };
			break;
		}

		switch (mType)
		{
		case SetTiles:
			mType = SetStart;
			mRotation = 0;
			break;

		case SetStart:
			mType = SetCheckpoint;
			
			mTrackObjects->SetStart({ mSize.x * (1 + mColIndex), mSize.y * (1 + mRowIndex) }, Size, Dir);

			mRotation = 0;

			break;

		case SetCheckpoint:
			mType = SetObstacles;

			mTrackObjects->SetCheckpoint({ mSize.x * (1 + mColIndex), mSize.y * (1 + mRowIndex) }, Size, Dir);

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
	Vector2 pos = { mSize.x * (1 + mColIndex), mSize.y * (1 + mRowIndex) };

	Rectangle rect = { pos.x - mSize.x / 2, pos.y - mSize.y / 2, mSize.x, mSize.y };

	Texture* text = mTileTexture;

	switch (mType)
	{
	case SetTiles:


		break;

	case SetStart:
		text = mStartTexture;
		rect = { pos.x - mSize.x / 2, pos.y - mSize.y / 2, mSize.x, mSize.y*3 };
		break;

	case SetCheckpoint:
		text = mCheckpointTexture;
		rect = { pos.x - mSize.x / 2, pos.y - mSize.y / 2, mSize.x, mSize.y*3 };
		break;

	case SetObstacles:
		text = mObstacleTexture;

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
