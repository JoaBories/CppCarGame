#include "Tile.h"
#include <string>
#include "Utils.h"

using std::string;
using std::to_string;

void Tile::DrawLayer(Rectangle rect, TileLayer layer) const
{
	if (layer.index == 0) return;
	
	TileLayer assetLayer = { layer.type, layer.index, 0 };
	Texture* text = AssetBank::GetInstance()->GetTileLayerTexture(assetLayer);
	DrawTexturePro(*text, {0,0,(float) text->width,(float) text->height}, rect, {rect.width * 0.5f, rect.height * 0.5f }, layer.rotation, WHITE);
}

Tile::Tile() :
	mSurfacingType{ Grass },
	mLayer0{ 0,1,0 },
	mLayer1{ 1,0,0 }
{
}

Tile::~Tile()
{
}

Tile::Tile(SurfacingType surface, TileLayer l0) :
	mSurfacingType{ surface },
	mLayer0{ 0,1,0 },
	mLayer1{ l0 }
{
}

void Tile::DrawLayer0(Vector2 position, Vector2 size) const
{
	float xCentered = position.x - size.x / 2;
	float yCentered = position.y - size.y / 2;

	Rectangle rect = Rectangle{ xCentered, yCentered, size.x, size.y };

	DrawLayer(rect, mLayer0);
}

void Tile::DrawLayer1(Vector2 position, Vector2 size) const
{
	float xCentered = position.x - size.x / 2;
	float yCentered = position.y - size.y / 2;

	Rectangle rect = Rectangle{ xCentered, yCentered, size.x, size.y };

	DrawLayer(rect, mLayer1);
}

int Tile::GetLayer1Index() const
{
	return mLayer1.index;
}

int Tile::GetLayer1Rot() const
{
	return mLayer1.rotation;
}

void Tile::SetLayer1Index(int i)
{
	mLayer1.index = i;
}

void Tile::SetLayer1Rot(int rot)
{
	mLayer1.rotation = rot;
}

