#include "raylib.h"

#include "Engine.h"

void Init();
void DeInit();
void UpdateDraw();
void Update();
void Draw();

Engine engine;

int screenHeight = 720;
int screenWidth = 1280;

Color backgroundColor = BLACK;

const char* gameName = "CarGame";

AssetBank* assetBank = nullptr;

int main() {

    Init();
    
    while (!WindowShouldClose()) {
        
        UpdateDraw();
    }

    
    return 0;
}

void Init()
{
    InitWindow(screenWidth, screenHeight, gameName);
    SetTargetFPS(60);

    assetBank = new AssetBank();

    engine.Init();
}

void DeInit()
{
    CloseWindow();

    delete assetBank;
}

void UpdateDraw()
{
    Update();

    BeginDrawing();
    Draw();

    ClearBackground(backgroundColor);
    EndDrawing();
}

void Update()
{
    engine.Update();
}

void Draw()
{
    engine.Draw();
}

