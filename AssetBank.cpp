#include "AssetBank.h"
using std::pair;

AssetBank* AssetBank::instance = nullptr;

Texture* AssetBank::LoadTextureFromSource(const char* source)
{
    Image img = LoadImage(source);
    Texture* textPtr = new Texture(LoadTextureFromImage(img));

    UnloadImage(img);

    return textPtr;
}

AssetBank::AssetBank()
{
    if (instance == nullptr) 
    {
        instance = this;
    }
    
    mTileLayers[{0, 1, 0}] = LoadTextureFromSource("resources/img/grass_1.png");

    mTileLayers[{1, 1, 0}] = LoadTextureFromSource("resources/img/sand_1.png");
    mTileLayers[{1, 2, 0}] = LoadTextureFromSource("resources/img/sand_2.png");
    mTileLayers[{1, 3, 0}] = LoadTextureFromSource("resources/img/sand_3.png");

    mTileLayers[{2, 1, 0}] = LoadTextureFromSource("resources/img/road_1.png");
    mTileLayers[{2, 2, 0}] = LoadTextureFromSource("resources/img/road_2.png");
    mTileLayers[{2, 3, 0}] = LoadTextureFromSource("resources/img/road_3.png");
    mTileLayers[{2, 4, 0}] = LoadTextureFromSource("resources/img/road_4.png");
    mTileLayers[{2, 5, 0}] = LoadTextureFromSource("resources/img/road_5.png");
    mTileLayers[{2, 6, 0}] = LoadTextureFromSource("resources/img/road_6.png");
    mTileLayers[{2, 7, 0}] = LoadTextureFromSource("resources/img/road_7.png");
    mTileLayers[{2, 8, 0}] = LoadTextureFromSource("resources/img/road_8.png");
    mTileLayers[{2, 9, 0}] = LoadTextureFromSource("resources/img/road_9.png");
}

AssetBank::~AssetBank()
{
    for (pair<TileLayer, Texture*> entry : mTileLayers) 
    {
        UnloadTexture(*entry.second);
        delete entry.second;
    }
}

AssetBank* AssetBank::GetInstance()
{
    return instance;
}

Texture* AssetBank::GetTileLayerTexture(TileLayer layer)
{
    return mTileLayers[layer];
}
