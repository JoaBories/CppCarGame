#include "AssetBank.h"

AssetBank* AssetBank::instance = nullptr;

Texture* AssetBank::LoadTextureFromSource(const char* source, float rotation)
{
    Image img = LoadImage(source);
    
    if (rotation != 0)
    {
        ImageRotate(&img, rotation);
    }

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
    
    mTileLayers[{0, 1, 0}] = LoadTextureFromSource("img/grass_1.png", 0);
}

AssetBank::~AssetBank()
{
}

AssetBank* AssetBank::GetInstance()
{
    return instance;
}

Texture* AssetBank::GetTileLayerTexture(TileLayer layer)
{
    return mTileLayers[layer];
}
