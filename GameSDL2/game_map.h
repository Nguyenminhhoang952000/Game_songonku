
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include"CommonFunc.h"
#include"BaseObject.h"

#define MAX_TILES 20

class TileMat : public BaseObject
{
public:
	TileMat() {;}
	~TileMat() {;}
};

class GameMap
{
public: 
		GameMap(){;}
		~GameMap(){;}

	void LoadMap(char* name);				// doc toan bo thong tin o trong cai file so do map
	void LoadTiles(SDL_Renderer* screen);   // load toan bo hinh anh 
	void DrawMap(SDL_Renderer* screen);		// xay dung map, lay hinh anh vao vi tri 
	Map getMap() const {return game_map_;};


	void SetMap(Map& map_data) {game_map_=map_data;};  // 
private:
	Map game_map_;							//Chua toan bo thong tin ve ban do(trang thai, vi tri, chi so cua o)
	TileMat tile_mat[MAX_TILES];			// doi tuong luu tru hinh anh 
	
};
#endif