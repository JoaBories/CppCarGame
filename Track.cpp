#include "Track.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

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

bool Track::IsThereASave() const
{
	ifstream file(mFileName);
	return file.good();
}

void Track::SaveTrack() const
{
	ofstream file(mFileName);
	if (!file) return;

	Checkpoint checkpoint = mTrackObjects->GetStart();
	file << "Start " << checkpoint.position.x << " " << checkpoint.position.y << " " << checkpoint.size.x << " " << checkpoint.size.y << " " << checkpoint.direction.x << " " << checkpoint.direction.y << " " << checkpoint.rotation << endl;
	checkpoint = mTrackObjects->GetCheckpoint();
	file << "Checkpoint " << checkpoint.position.x << " " << checkpoint.position.y << " " << checkpoint.size.x << " " << checkpoint.size.y << " " << checkpoint.direction.x << " " << checkpoint.direction.y << " " << checkpoint.rotation << endl;
	
	vector<Obstacles> obstacles = mTrackObjects->GetObstacles();
	file << "Obstacles " << obstacles.size() << endl;
	for (size_t i = 0; i < obstacles.size(); i++)
	{
		file << i << "- " << obstacles[i].GetPosition().x << " " << obstacles[i].GetPosition().y << " " << obstacles[i].GetSize().x << " " << obstacles[i].GetSize().y << " " << obstacles[i].GetRotation() << endl;
	}

	file << "Tilemap " << mTilemap->GetRows() << " " << mTilemap->GetCols() << endl;
	for (size_t r = 0; r < mTilemap->GetRows(); r++)
	{
		for (size_t c = 0; c < mTilemap->GetCols(); c++)
		{
			file << mTilemap->GetTile(r, c)->GetLayer1Index() << " " << mTilemap->GetTile(r, c)->GetLayer1Rot() << "   ";
		}
		file << endl;
	}

	file << "End" << endl;

	file.close();
}

void Track::LoadTrack()
{

	if (IsThereASave())
	{
		ifstream file(mFileName);
		if (!file) return;

		int a, b, c, d, e, f, g;
		string label;

		file >> label;
		file >> a >> b >> c >> d >> e >> f >> g;
		mTrackObjects->SetStart({(float) a, (float)b}, {(float) c, (float) d}, {(float) e, (float) f}, g);

		file >> label;
		file >> a >> b >> c >> d >> e >> f >> g;
		mTrackObjects->SetCheckpoint({(float) a, (float)b}, {(float) c, (float) d}, {(float) e, (float) f}, g);

		file >> label;
		file >> a;

		mTrackObjects->ClearObstacles();
		for (size_t i = 0; i < a; i++)
		{
			file >> label;
			file >> b >> c >> d >> e >> f;
			mTrackObjects->AddObstacle(Obstacles({ (float)b, (float)c }, { (float)d, (float)e }, f));
		}

		file >> label;
		file >> a >> b;

		for (size_t r = 0; r < a; r++)
		{
			for (size_t col = 0; col < b; col++)
			{
				file >> c >> d;
				mTilemap->GetTile(r, col)->SetLayer1Index(c);
				mTilemap->GetTile(r, col)->SetLayer1Rot(d);
			}
		}
	}

}
