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

void TrackObjects::DrawObstacles() const
{
	for (Obstacles obstacle : mObstacles)
	{
		obstacle.Draw();
	}
}

void TrackObjects::SetStart(Vector2 position, Vector2 size, Vector2 direction, int rotation)
{
	mStart = { position, size, direction, rotation };
	cout << "Start set to: " << mStart.position.x << ", " << mStart.position.y << endl;
	cout << "Size set to: " << mStart.size.x << ", " << mStart.size.y << endl;
	cout << "Direction set to: " << mStart.direction.x << ", " << mStart.direction.y << endl;
}

void TrackObjects::SetCheckpoint(Vector2 position, Vector2 size, Vector2 direction, int rotation)
{
	mCheckpoint = { position, size, direction, rotation };
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

void TrackObjects::AddObstacle(Obstacles obstacle)
{
	mObstacles.push_back(obstacle);
	cout << "Obstacle set to: " << obstacle.GetPosition().x << ", " << obstacle.GetPosition().y << endl;
	cout << "Size set to: " << obstacle.GetSize().x << ", " << obstacle.GetSize().y << endl;
}

void TrackObjects::RemoveObstacle(int index)
{
	mObstacles.erase(mObstacles.begin() + index);
}
