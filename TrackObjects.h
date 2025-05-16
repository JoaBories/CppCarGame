#pragma once
#include "raylib.h"
#include <vector>

using std::vector;

#include "Obstacles.h"


struct Checkpoint
{
	Vector2 position;
	Vector2 size;
	Vector2 direction;
	int rotation;
};

class TrackObjects
{
private :
	Checkpoint mStart;
	Checkpoint mCheckpoint;
	vector<Obstacles> mObstacles;

public :
	TrackObjects();
	~TrackObjects();

	void DrawObstacles() const;

	void SetStart(Vector2 position, Vector2 size, Vector2 direction, int rotation);
	void SetCheckpoint(Vector2 position, Vector2 size, Vector2 direction, int rotation);

	Checkpoint GetStart() const;
	Checkpoint GetCheckpoint() const;

	vector<Obstacles> GetObstacles() const;
	void AddObstacle(Obstacles obstacle);
	void RemoveObstacle(int index);
	void ClearObstacles();
};

