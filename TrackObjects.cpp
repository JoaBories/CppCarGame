#include "TrackObjects.h"

#include "Utils.h"

TrackObjects::TrackObjects() :
	mStart{ { 0, 0 }, { 0, 0 }, { 0, 0 } },
	mCheckpoint{ { 0, 0 }, { 0, 0 }, { 0, 0 } },
	mObstacles{}
{
}

TrackObjects::~TrackObjects()
{
}

void TrackObjects::Draw() const
{
	for (Obstacles obstacle : mObstacles)
	{
		obstacle.Draw();
	}
}

void TrackObjects::SetStart(Vector2 position, Vector2 size, Vector2 direction)
{
	mStart = { position, size, direction };
	cout << "Start set to: " << mStart.position.x << ", " << mStart.position.y << endl;
	cout << "Size set to: " << mStart.size.x << ", " << mStart.size.y << endl;
	cout << "Direction set to: " << mStart.direction.x << ", " << mStart.direction.y << endl;
}

void TrackObjects::SetCheckpoint(Vector2 position, Vector2 size, Vector2 direction)
{
	mCheckpoint = { position, size, direction };
	cout << "Checkpoint set to: " << mCheckpoint.position.x << ", " << mCheckpoint.position.y << endl;
	cout << "Size set to: " << mCheckpoint.size.x << ", " << mCheckpoint.size.y << endl;
	cout << "Direction set to: " << mCheckpoint.direction.x << ", " << mCheckpoint.direction.y << endl;
}

Checkpoint TrackObjects::GetStart() const
{
	return mStart;
}

Checkpoint TrackObjects::GetCheckpoint() const
{
	return mCheckpoint;
}

vector<Obstacles> TrackObjects::GetObstacles() const
{
	return mObstacles;
}
