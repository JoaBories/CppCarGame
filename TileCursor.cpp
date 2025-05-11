#include "TileCursor.h"

TileCursor::TileCursor() :
	mRowIndex{ 0 },
	mColIndex{ 0 },
	mRowMax{ 0 },
	mColMax{ 0 },
	mSize{ 0, 0 },
	mType{ Tiles },
	mTilemap{ nullptr },
	mTileTexture{ nullptr },
	mStartTexture{ nullptr },
	mCheckpointTexture{ nullptr },
	mObstacleTexture{ nullptr }
{
}

TileCursor::~TileCursor()
{
}

TileCursor::TileCursor(int maxRow, int maxCol, Vector2 size, Tilemap* mTilemap) :
	mRowIndex{ 0 },
	mColIndex{ 0 },
	mRowMax{ maxRow },
	mColMax{ maxCol },
	mSize{ size },
	mType{ Tiles },
	mTilemap{ mTilemap },
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
	case Tiles:
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

	case Start:
		if (IsKeyPressed(KEY_R))
		{
			mRotation += 90;

			if (mRotation == 360)
			{
				mRotation = 0;
			}
		}

		break;

	case Checkpoint:
		if (IsKeyPressed(KEY_R))
		{
			mRotation += 90;

			if (mRotation == 360)
			{
				mRotation = 0;
			}
		}

		break;

	case Obstacle:
		break;

	}

	if (IsKeyPressed(KEY_ENTER))
	{
		switch (mType)
		{
		case Tiles:
			mType = Start;
			mRotation = 0;
			break;

		case Start:
			mType = Checkpoint;
			mRotation = 0;
			break;

		case Checkpoint:
			mType = Obstacle;
			mRotation = 0;
			break;

		case Obstacle:
			mType = Tiles;
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
	case Tiles:


		break;

	case Start:
		text = mStartTexture;
		rect = { pos.x - mSize.x / 2, pos.y - mSize.y / 2, mSize.x, mSize.y*3 };
		break;

	case Checkpoint:
		text = mCheckpointTexture;
		rect = { pos.x - mSize.x / 2, pos.y - mSize.y / 2, mSize.x, mSize.y*3 };
		break;

	case Obstacle:
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
