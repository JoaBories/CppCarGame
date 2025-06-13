#include "Tilemap.h"

Tilemap::Tilemap() :
	mTiles{ {} },
	mScreenSize{ 0,0 },
	mTileSize{ 0,0 }
{
}

Tilemap::~Tilemap()
{
	for (vector<Tile *> row : mTiles)
	{
		for (Tile* tile : row) 
		{
			delete tile;
		}
	}
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
			Vector2 pos = { mTileSize.x * (0.5 + c), mTileSize.y * (0.5 + r)};
			mTiles[r][c]->DrawLayer0(pos, mTileSize);
		}
	}

	for (size_t r = 0; r < mTiles.size(); r++)
	{
		for (size_t c = 0; c < mTiles[r].size(); c++)
		{
			Vector2 pos = { mTileSize.x * (0.5 + c), mTileSize.y * (0.5 + r) };
			mTiles[r][c]->DrawLayer1(pos, mTileSize);
		}
	}
}

Vector2 Tilemap::GetTileSize() const
{
	return mTileSize;
}

Tile* Tilemap::GetTile(int row, int col) const
{
	return mTiles[row][col];
}

int Tilemap::GetRows() const
{
	return mTiles.size();
}

int Tilemap::GetCols() const
{
	return mTiles[0].size();
}