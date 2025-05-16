#pragma once
#include "Tilemap.h"
#include "TrackObjects.h"


class Track
{
private :
	Tilemap* mTilemap;
	TrackObjects* mTrackObjects;

	string mFileName = "resources/track/01.track";

public :
	Track();
	~Track();

	void Draw() const;

	Tilemap* GetTilemap() const;
	TrackObjects* GetTrackObjects() const;

	bool IsThereASave() const;

	void SaveTrack() const;
	void LoadTrack();

};

