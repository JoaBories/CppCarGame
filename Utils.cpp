#include "Utils.h"


Utils::Utils()
{
}

Utils::~Utils()
{
}

float Utils::SqrLenght(Vector2 vector)
{
	return (vector.x * vector.x) + (vector.y * vector.y);
}

float Utils::Lenght(Vector2 vector)
{
	return sqrtf(SqrLenght(vector));
}

Vector2 Utils::Normalize(Vector2 vector)
{
	if (vector.x == 0 && vector.y == 0) return { 0, 0 };
	float l = Lenght(vector);
	return { vector.x/l, vector.y/l };
}

Vector2 Utils::Vector2Substract(Vector2 a, Vector2 b)
{
	return { a.x - b.x, a.y - b.y };
}

Vector2 Utils::Vector2Distance(Vector2 a, Vector2 b)
{
	Vector2 d = Vector2Substract(a, b);
	return { Abs(d.x), Abs(d.y) };
}

float Utils::RotFromVector2(Vector2 vector)
{
	if (vector.x == 0 && vector.y == 0) return 0;
	float a = atan2f(vector.y, vector.x) * RAD2DEG;
	if (a < 0) a += 360;
	return a;
}

Vector2 Utils::Vector2FromRot(float angle)
{
	Vector2 vector = { cosf(angle * DEG2RAD), sinf(angle * DEG2RAD) };
	return Normalize(vector);
}

float Utils::DotProduct(Vector2 a, Vector2 b)
{
	return (a.x * b.x) + (a.y * b.y);
}

Vector2 Utils::Vector2Scale(Vector2 vector, float scale)
{
	return { vector.x * scale, vector.y * scale };
}

Vector2 Utils::Vector2Add(Vector2 a, Vector2 b)
{
	return { a.x + b.x, a.y + b.y };
}

Vector2 Utils::Vector2Negate(Vector2 vector)
{
	return { -vector.x, -vector.y };
}

float Utils::Min(float a, float b)
{
	return (a <= b) ? a : b;
}

float Utils::Max(float a, float b)
{
	return (a >= b) ? a : b;
}

float Utils::Abs(float value)
{
	return (value < 0) ? -value : value;
}

float Utils::Clamp(float value, float min, float max)
{
	return Max(Min(value, max), min);
}

float Utils::Lerp(float a, float b, float t)
{
	return a + ( b - a ) * Clamp(t, 0, 1);
}

Vector2 Utils::Vector2Lerp(Vector2 a, Vector2 b, float t)
{
	return { Lerp(a.x, b.x, t), Lerp(a.y, b.y, t) };
}

Color Utils::ColorLerp(Color a, Color b, float t)
{
	Color result = Color();
	result.r = Lerp(a.r, b.r, t);
	result.g = Lerp(a.g, b.g, t);
	result.b = Lerp(a.b, b.b, t);
	result.a = Lerp(a.a, b.a, t);
	return result;
}

float Utils::Sign(float value)
{
	return (value >= 0) ? 1 : -1;
}

int Utils::RandInt(int min, int max)
{
	static random_device rd;
	static mt19937 gen(rd());

	uniform_int_distribution<> distr(min, max);
	return distr(gen);
}

vector<Vector2> Utils::GetCorners(Rectangle rect, float rotation)
{
	vector<Vector2> corners(4);
	float cosA = cosf(rotation * DEG2RAD);
	float sinA = sinf(rotation * DEG2RAD);

	Vector2 right = { cosA, sinA };
	Vector2 up = { -sinA, cosA };

	corners[0] = Vector2Add({ rect.x, rect.y }, Vector2Add(Vector2Scale(right, rect.width * 0.5f), Vector2Scale(up, rect.height * 0.5f)));
	corners[1] = Vector2Add({ rect.x, rect.y }, Vector2Add(Vector2Scale(right, -rect.width * 0.5f), Vector2Scale(up, rect.height * 0.5f)));
	corners[2] = Vector2Add({ rect.x, rect.y }, Vector2Add(Vector2Scale(right, -rect.width * 0.5f), Vector2Scale(up, -rect.height * 0.5f)));
	corners[3] = Vector2Add({ rect.x, rect.y }, Vector2Add(Vector2Scale(right, rect.width * 0.5f), Vector2Scale(up, -rect.height * 0.5f)));

	return corners;
}

float Utils::OverlapOnAxis(const vector<Vector2>& a, const vector<Vector2>& b, Vector2 axis)
{
	float minA = FLT_MAX, maxA = -FLT_MAX;
	float minB = FLT_MAX, maxB = -FLT_MAX;

	for (const auto& point : a)
	{
		float projection = DotProduct(point, axis);
		minA = Min(minA, projection);
		maxA = Max(maxA, projection);
	}

	for (const auto& point : b)
	{
		float projection = DotProduct(point, axis);
		minB = Min(minB, projection);
		maxB = Max(maxB, projection);
	}

	return Min(maxA, maxB) - Max(minA, minB);
}

OBBCollision Utils::CheckOBB(const Rectangle& a, const int& aRot, const Rectangle& b, const int& bRot)
{
	vector<Vector2> cornersA = GetCorners(a, aRot);
	vector<Vector2> cornersB = GetCorners(b, bRot);

	vector<Vector2> axes;

	Vector2 edge;
	Vector2 normal;

	OBBCollision collision;

	edge = Vector2Substract(cornersA[0], cornersA[1]);
	normal = { -edge.y, edge.x };
	axes.push_back(Normalize(Normalize(normal)));

	edge = Vector2Substract(cornersA[1], cornersA[2]);
	normal = { -edge.y, edge.x };
	axes.push_back(Normalize(Normalize(normal)));

	edge = Vector2Substract(cornersB[0], cornersB[1]);
	normal = { -edge.y, edge.x };
	axes.push_back(Normalize(Normalize(normal)));

	edge = Vector2Substract(cornersB[1], cornersB[2]);
	normal = { -edge.y, edge.x };
	axes.push_back(Normalize(Normalize(normal)));

	// ====================================== DEBUG DRAWING =========================================
	//DrawCircleV(cornersA[0], 5, BLUE);
	//DrawCircleV(cornersA[1], 5, GREEN);
	//DrawCircleV(cornersA[2], 5, RED);
	//DrawCircleV(cornersA[3], 5, YELLOW);
	//
	//DrawCircleV(cornersB[0], 5, BLUE);
	//DrawCircleV(cornersB[1], 5, GREEN);
	//DrawCircleV(cornersB[2], 5, RED);
	//DrawCircleV(cornersB[3], 5, YELLOW);
	//
	//for (int i = 0; i < 4; ++i)
	//	DrawLineV(cornersA[i], cornersA[(i + 1) % 4], RED);
	//
	//for (int i = 0; i < 4; ++i)
	//	DrawLineV(cornersB[i], cornersB[(i + 1) % 4], BLUE);
	//
	//Vector2 axiss;
	//axiss = axes[0];
	//DrawLineV(Vector2Add({ a.x, a.y }, Vector2Scale(axiss, 50)), Vector2Add({ a.x, a.y }, Vector2Scale(axiss, -50)), VIOLET);
	//if (!OverlapOnAxis(cornersA, cornersB, axes[0]))
	//{
	//	DrawLineV(Vector2Add({ a.x, a.y }, Vector2Scale(axiss, 50)), Vector2Add({ a.x, a.y }, Vector2Scale(axiss, -50)), RED);
	//}
	//
	//axiss = axes[1];
	//DrawLineV(Vector2Add({ a.x, a.y }, Vector2Scale(axiss, 50)), Vector2Add({ a.x, a.y }, Vector2Scale(axiss, -50)), GREEN);
	//if (!OverlapOnAxis(cornersA, cornersB, axes[1]))
	//{
	//	DrawLineV(Vector2Add({ a.x, a.y }, Vector2Scale(axiss, 50)), Vector2Add({ a.x, a.y }, Vector2Scale(axiss, -50)), RED);
	//}
	//
	//axiss = axes[2];
	//DrawLineV(Vector2Add({ b.x, b.y }, Vector2Scale(axiss, 50)), Vector2Add({ b.x, b.y }, Vector2Scale(axiss, -50)), BLUE);
	//if (!OverlapOnAxis(cornersA, cornersB, axes[2]))
	//{
	//	DrawLineV(Vector2Add({ b.x, b.y }, Vector2Scale(axiss, 50)), Vector2Add({ b.x, b.y }, Vector2Scale(axiss, -50)), RED);
	//}
	//
	//axiss = axes[3];
	//DrawLineV(Vector2Add({ b.x, b.y }, Vector2Scale(axiss, 50)), Vector2Add({ b.x, b.y }, Vector2Scale(axiss, -50)), YELLOW);
	//if (!OverlapOnAxis(cornersA, cornersB, axes[3]))
	//{
	//	DrawLineV(Vector2Add({ b.x, b.y }, Vector2Scale(axiss, 50)), Vector2Add({ b.x, b.y }, Vector2Scale(axiss, -50)), RED);
	//}
	// 
	// ===============================================================================================

	for (const auto& axis : axes)
	{
		float overlap = OverlapOnAxis(cornersA, cornersB, axis);

		if (overlap < 0)
		{
			collision.collision = false;
			return collision;
		}
		else if (overlap < collision.minTranslationOverlap)
		{
			collision.minTranslationOverlap = overlap;
			collision.minTranslationAxis = axis;
		}
	}

	collision.collision = true;
	return collision;
}

void Utils::DrawTextCentered(string text, Vector2 position, int fontSize)
{
	float xCentered = position.x - (float) MeasureText(text.c_str(), fontSize) / 2;
	float yCentered = position.y - fontSize / 2;
	DrawText(text.c_str(), xCentered, yCentered, fontSize, WHITE);
}

void Utils::DrawTextCentered(string text, Vector2 position, int fontSize, Color color)
{
	float xCentered = position.x - (float)MeasureText(text.c_str(), fontSize) / 2;
	float yCentered = position.y - fontSize / 2;
	DrawText(text.c_str(), xCentered, yCentered, fontSize, color);
}

void Utils::DrawRectangleCentered(Rectangle rect, Color color)
{
	float xCentered = rect.x - rect.width * 0.5f;
	float yCentered = rect.y - rect.height * 0.5f;
	DrawRectangle(xCentered, yCentered, rect.width, rect.height, color);
}

void Utils::DrawTextWithBackground(string text, Vector2 position, float fontSize, Color textColor, Color backgroundColor, int padding)
{
	float textWidth = MeasureText(text.c_str(), fontSize);
	float textHeight = fontSize;
	float xCentered = position.x - textWidth / 2;
	float yCentered = position.y - textHeight / 2;

	DrawRectangle(xCentered - padding, yCentered - padding, textWidth + padding * 2, textHeight + padding * 2, backgroundColor);

	DrawText(text.c_str(), xCentered, yCentered, fontSize, textColor);
}
