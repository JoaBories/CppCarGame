#pragma once
#include "raylib.h"
#include <map>

using std::map;

struct TileLayer // 0,0,0 -> empty layer
{
public :

	int type;
	int index;
	int rotation; // 0,90,180,270

	TileLayer(int type, int index, int rot) :
		type{type},
		index{index},
		rotation{rot}
	{
	}

	bool operator<(const TileLayer& other) const {
		// Simple lexicographic comparison
		return std::tie(type, index, rotation) < std::tie(other.type, other.index, other.rotation);
	}
};


class AssetBank
{
private :
	map<TileLayer, Texture*> mTileLayers;

	Texture* LoadTextureFromSource(const char* source);

public :
	AssetBank();
	~AssetBank();

	static AssetBank* instance;
	static AssetBank* GetInstance();

	Texture* GetTileLayerTexture(TileLayer layer);
};

