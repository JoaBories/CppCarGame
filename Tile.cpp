#include "Tile.h"
#include <string>

using std::string;
using std::to_string;

void Tile::DrawLayer(Rectangle rect, TileLayer layer) const
{
	DrawTextureRec(*AssetBank::GetInstance()->GetTileLayerTexture(layer), rect, {rect.x, rect.y}, WHITE);
}

Tile::Tile() :
	mSurfacingType{ Grass },
	mLayer0{ 0,1,0 },
	mLayer1{ 0,0,0 },
	mLayer2{ 0,0,0 }
{
}

Tile::~Tile()
{
}

Tile::Tile(SurfacingType surface, TileLayer l0, TileLayer l1, TileLayer l2) :
	mSurfacingType{ surface },
	mLayer0{ l0 },
	mLayer1{ l1 },
	mLayer2{ l2 }
{
}

void Tile::Draw(Vector2 position, Vector2 size) const
{
	float xCentered = position.x - size.x / 2;
	float yCentered = position.y - size.y / 2;

	Rectangle rect = Rectangle{ xCentered, yCentered, size.x, size.y };

	DrawLayer(rect, mLayer0);
	DrawLayer(rect, mLayer1);
	DrawLayer(rect, mLayer2);
}

