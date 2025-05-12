#include "Track.h"

Track::Track()
{
	mTilemap = new Tilemap(9, 16);
	mTrackObjects = new TrackObjects();
}

Track::~Track()
{
}

void Track::Draw() const
{
	mTilemap->Draw();
	mTrackObjects->DrawObstacles();
}

Tilemap* Track::GetTilemap() const
{
	return mTilemap;
}

TrackObjects* Track::GetTrackObjects() const
{
	return mTrackObjects;
}

void Track::SaveTrack() const
{

	//filesave

}

void Track::LoadTrack()
{

	//fileload

}
