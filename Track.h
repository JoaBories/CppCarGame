#pragma once
#include "Tilemap.h"
#include "TrackObjects.h"


class Track
{
private :
	Tilemap* mTilemap;
	TrackObjects* mTrackObjects;

public :
	Track();
	~Track();

	void Draw() const;

	Tilemap* GetTilemap() const;
	TrackObjects* GetTrackObjects() const;

	void SaveTrack() const;
	void LoadTrack();

};

