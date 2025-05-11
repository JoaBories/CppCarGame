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

	void Draw() const;

	void SetStart(Vector2 position, Vector2 size, Vector2 direction);
	void SetCheckpoint(Vector2 position, Vector2 size, Vector2 direction);

	Checkpoint GetStart() const;
	Checkpoint GetCheckpoint() const;

	vector<Obstacles> GetObstacles() const;
};

