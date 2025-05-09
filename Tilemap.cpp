#include "Tilemap.h"

Tilemap::Tilemap() :
	mTiles{ {} },
	mScreenSize{ 0,0 },
	mTileSize{ 0,0 }
{
}

Tilemap::~Tilemap()
{
}

Tilemap::Tilemap(int rows, int cols) :
	mScreenSize{ (float) GetScreenWidth(), (float) GetScreenHeight() },
	mTileSize{ (float) GetScreenWidth()/cols, (float) GetScreenHeight()/rows },
	mTiles{ {} }
{
	mTiles.clear();
	for (size_t r = 0; r < rows; r++)
	{
		mTiles.push_back({});
		for (size_t c = 0; c < cols; c++)
		{
			mTiles[r].push_back(new Tile());
		}
	}
}

void Tilemap::Draw() const
{
	for (size_t r = 0; r < mTiles.size(); r++)
	{
		for (size_t c = 0; c < mTiles[r].size(); c++)
		{
			Vector2 pos = { mTileSize.x * (1 + c), mTileSize.y * (1 + r)};
			mTiles[r][c]->Draw(pos, mTileSize);
		}
	}
}
