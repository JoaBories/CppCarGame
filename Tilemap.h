#pragma once
#include "Tile.h"
#include <vector>
#include "Utils.h"

using std::vector;

class Tilemap
{
private :
	vector<vector<Tile*>> mTiles; //[row[col, col, ...], row[col, col, ...], ...]
	Vector2 mScreenSize;
	Vector2 mTileSize;

public :
	Tilemap();
	~Tilemap();
	Tilemap(int rows, int cols);

	void Draw() const;

	Vector2 GetTileSize() const;

	Tile* GetTile(int row, int col) const;

	int GetRows() const;
	int GetCols() const;
};

