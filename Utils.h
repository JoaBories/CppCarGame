#pragma once
#include "raylib.h"

#include <iostream>
using std::cout;
using std::endl;

#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

using std::string;

#include <vector>
using std::vector;

#include <cmath>

struct OBBCollision 
{
	bool collision;
	Vector2 minTranslationAxis;
	float minTranslationOverlap = FLT_MAX;
};

class Utils
{
private:
	Utils();
	~Utils();

public:
	//Math functions
	static float SqrLenght(Vector2 vector);
	static float Lenght(Vector2 vector);
	static Vector2 Normalize(Vector2 vector);
	static Vector2 Vector2Substract(Vector2 a, Vector2 b);
	static Vector2 Vector2Distance(Vector2 a, Vector2 b);
	static float RotFromVector2(Vector2 vector);
	static Vector2 Vector2FromRot(float rot);
	static float DotProduct(Vector2 a, Vector2 b);
	static Vector2 Vector2Scale(Vector2 vector, float scale);
	static Vector2 Vector2Add(Vector2 a, Vector2 b);
	static Vector2 Vector2Negate(Vector2 vector);

	static float Min(float a, float b);
	static float Max(float a, float b);
	static float Clamp(float value, float min, float max);
	static float Abs(float value);
	static float Sign(float value);

	static float Lerp(float a, float b, float t);
	static Color ColorLerp(Color a, Color b, float t);
	static Vector2 Vector2Lerp(Vector2 a, Vector2 b, float t);

	static int RandInt(int min, int max);

	static vector<Vector2> GetCorners(Rectangle rect, float rotation);
	static float OverlapOnAxis(const vector<Vector2>& a, const vector<Vector2>& b, Vector2 axis);
	static OBBCollision CheckOBB(const Rectangle& a, const int& aRot, const Rectangle& b, const int& bRot);

	//Text functions
	static void DrawTextCentered(string text, Vector2 position, int fontSize);
	static void DrawTextCentered(string text, Vector2 position, int fontSize, Color color);
	static void DrawRectangleCentered(Rectangle rect, Color color);

	static void DrawTextWithBackground(string text, Vector2 position, float fontSize, Color textColor, Color backgroundColor, int padding);
};
