#ifndef OccupancyMapH
#define OccupancyMapH

#include <vector>
#include <memory>
#include "TileMap.h"
#include "Sprite.h"

using namespace std;

class OccupancyMap{
public:
	OccupancyMap(int x, int y);
	~OccupancyMap();
	vector<int> Update(TileMap *tileMap, vector<unique_ptr<GameObject>> *objectArray);
	vector<int> CreateHeuristic(TileMap *tileMap, Point door, int RoomID);
	void Render(TileMap *tileMap);
	void CleanTile(TileMap *tileMap, Point tile);

	vector<int> occupancyMap;

private:
	Sprite sp;
	vector<int> heuristics;
};


#endif

