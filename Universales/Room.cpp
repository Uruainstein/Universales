#include "Room.h"
#include "Camera.h"
#include "Wall.h"

Room::Room(Point lBegin, Point lEnd, TileMap *tileMap, vector<unique_ptr<GameObject> > *objectArray, int RoomCount, RoomType type) : tileSp("img/tileset/tile_tatami.png"), tileMap(*tileMap){

	Point tile;
	begin = lBegin;
	end = lEnd;
	string file;
	door = Point(0, 0);
	RoomID = RoomCount + 1;
	roomType = type;
	switch (roomType)
	{
	case CORRIDOR:
		tileSp.Open("img/tileset/fundo_espaco.png");
		break;
	case SAMURAI:
		break;
	case PIRATE:
		tileSp.Open("img/tileset/tile_madeira.png");
		break;
	case STEAM:
		break;
	default:
		break;
	}

	file = "img/tile_parede_canto_sup_tamanho_do_tile.png";
	Point pos(begin.x, begin.y);
	tile = pos;
	pos = tileMap->GetTileCenter(pos);
	//cout << begin.x << "," << begin.y << endl;
	Wall *wall = new Wall (pos.x - tileMap->GetTileWidth() / 2, pos.y + tileMap->GetTileHeight() / 2, file, UPPER_CORNER, tile, tileMap, RoomID);
	objectArray->emplace_back(wall);

	file = "img/tile_parede_canto_esq_tamanho_do_tile.png";
	pos.SetPoint(begin.x, end.y);
	tile = pos;
	pos = tileMap->GetTileCenter(pos);
	wall = new Wall(pos.x - tileMap->GetTileWidth() / 2, pos.y + tileMap->GetTileHeight() / 2, file, LEFT_CORNER, tile,tileMap, RoomID);
	objectArray->emplace_back(wall);

	file = "img/tile_parede_canto_dir_tamanho_do_tile.png";
	pos.SetPoint(end.x, begin.y);
	tile = pos;
	pos = tileMap->GetTileCenter(pos);
	wall = new Wall(pos.x - tileMap->GetTileWidth() / 2, pos.y + tileMap->GetTileHeight() / 2, file, RIGHT_CORNER, tile,tileMap, RoomID);
	objectArray->emplace_back(wall);

	file = "img/tile_parede_canto_inf_tamanho_do_tile.png";
	pos.SetPoint(end.x, end.y);
	tile = pos;
	pos = tileMap->GetTileCenter(pos);
	wall = new Wall(pos.x - tileMap->GetTileWidth() / 2, pos.y + tileMap->GetTileHeight() / 2, file, INF_CORNER, tile, tileMap ,RoomID);
	objectArray->emplace_back(wall);


	file = "img/parede_dir_tamanho_do_tile.png";
	for (int i = begin.x + 1; i< end.x; i++){
		Point pos(i, begin.y);
		tile = pos;
		
			pos = tileMap->GetTileCenter(pos);
			wall = new Wall(pos.x - tileMap->GetTileWidth() / 2, pos.y + tileMap->GetTileHeight() / 2, file, UPPER_RIGHT, tile, tileMap, RoomID);
			objectArray->emplace_back(wall);
	
			pos.SetPoint(i, end.y);
			tile = pos;
			pos = tileMap->GetTileCenter(pos);
			wall = new Wall(pos.x - tileMap->GetTileWidth() / 2, pos.y + tileMap->GetTileHeight() / 2, file, UPPER_RIGHT, tile,tileMap, RoomID);
			objectArray->emplace_back(wall);
		
	}
	/*for(int i = begin.x+1; i< end.x; i++){
	Point pos(i,begin.y-1);
	pos = tileMap->GetTileCenter(pos);
	Wall *wall = new Wall(pos.x-tileMap->GetTileWidth()/4, pos.y+tileMap->GetTileHeigh()/4, file, UPPER_RIGHT);
	objectArray->emplace_back(wall);
	}*/
	file = "img/parede_esq_tamanho_do_tile.png";
	for (int i = begin.y + 1; i< end.y; i++){
		Point pos(begin.x, i);
		tile = pos;
		
			pos = tileMap->GetTileCenter(pos);
			wall = new Wall(pos.x - tileMap->GetTileWidth() / 2, pos.y + tileMap->GetTileHeight() / 2, file, UPPER_LEFT, tile,tileMap, RoomID);
			objectArray->emplace_back(wall);
		

		pos.SetPoint(end.x, i);
		tile = pos;
		
			pos = tileMap->GetTileCenter(pos);
			wall = new Wall(pos.x - tileMap->GetTileWidth() / 2, pos.y + tileMap->GetTileHeight() / 2, file, UPPER_LEFT, tile,tileMap,RoomID);
			objectArray->emplace_back(wall);

	}

}

void Room::EditRoom(bool editing) {
	if (editing)
		roomState = EDITING;
	else
		roomState = NONE;
}

void Room::Render(TileMap *tileMap){
	editTimer.Update(Game::GetInstance().GetDeltaTime());
	if (roomState == EDITING) {
		if (editTimer.Get() < 0.04){
			Point renderPos;
			if (end.x < begin.x){
				if (end.y < begin.y){
					for (int i = end.x; i <= begin.x; i++){
						for (int j = end.y; j <= begin.y; j++){
							if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
								Point tile(i, j);
								renderPos = tileMap->GetTileCenter(tile);
								tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
							}
						}
					}
				}
				else{
					for (int i = end.x; i <= begin.x; i++){
						for (int j = begin.y; j <= end.y; j++){
							if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
								Point tile(i, j);
								renderPos = tileMap->GetTileCenter(tile);
								tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
							}
						}
					}
				}
			}
			else{
				if (end.y < begin.y){
					for (int i = begin.x; i <= end.x; i++){
						for (int j = end.y; j <= begin.y; j++){
							if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
								Point tile(i, j);
								renderPos = tileMap->GetTileCenter(tile);
								tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
							}
						}
					}
				}
				else{
					for (int i = begin.x; i <= end.x; i++){
						for (int j = begin.y; j <= end.y; j++){
							if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
								Point tile(i, j);
								renderPos = tileMap->GetTileCenter(tile);
								tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
							}
						}
					}
				}
			}
		}
		if (editTimer.Get() > 0.09)
			editTimer.Restart();
	}
	else {
		Point renderPos;
		if (end.x < begin.x){
			if (end.y < begin.y){
				for (int i = end.x; i <= begin.x; i++){
					for (int j = end.y; j <= begin.y; j++){
						if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
							Point tile(i, j);
							renderPos = tileMap->GetTileCenter(tile);
							tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
						}
					}
				}
			}
			else{
				for (int i = end.x; i <= begin.x; i++){
					for (int j = begin.y; j <= end.y; j++){
						if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
							Point tile(i, j);
							renderPos = tileMap->GetTileCenter(tile);
							tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
						}
					}
				}
			}
		}
		else{
			if (end.y < begin.y){
				for (int i = begin.x; i <= end.x; i++){
					for (int j = end.y; j <= begin.y; j++){
						if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
							Point tile(i, j);
							renderPos = tileMap->GetTileCenter(tile);
							tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
						}
					}
				}
			}
			else{
				for (int i = begin.x; i <= end.x; i++){
					for (int j = begin.y; j <= end.y; j++){
						if (i >= 0 && j >= 0 && i < tileMap->GetWidth() && j < tileMap->GetHeight()){
							Point tile(i, j);
							renderPos = tileMap->GetTileCenter(tile);
							tileSp.Render(renderPos.x - tileSp.GetWidth() / 2 + Camera::pos.x, renderPos.y - tileSp.GetHeight() / 2 + Camera::pos.y);
						}
					}
				}
			}
		}
	}
}

void Room::SetDoor(float x, float y, int RoomID, vector<unique_ptr<GameObject> > *objectArray) {
	Point aux = door;
	if ((aux.y < end.y) && (aux.x == end.x)){
		Point p(tileMap.GetTileCenter(aux));
		string file = "img/parede_esq_tamanho_do_tile.png";
		Wall *wall = new Wall(p.x - tileMap.GetTileWidth() / 2, p.y + tileMap.GetTileHeight() / 2, file, UPPER_LEFT, aux, &tileMap ,RoomID);
		objectArray->emplace_back(wall);
	}
	if ((aux.y > begin.y) && (aux.x == begin.x)){
		Point p(tileMap.GetTileCenter(aux));
		string file = "img/parede_esq_tamanho_do_tile.png";
		Wall *wall = new Wall(p.x - tileMap.GetTileWidth() / 2, p.y + tileMap.GetTileHeight() / 2, file, UPPER_LEFT, aux, &tileMap,RoomID);
		objectArray->emplace_back(wall);
	}
	if ((aux.x < end.x) && (aux.y == end.y)){
		Point p(tileMap.GetTileCenter(aux));
		string file = "img/parede_dir_tamanho_do_tile.png";
		Wall *wall = new Wall(p.x - tileMap.GetTileWidth() / 2, p.y + tileMap.GetTileHeight() / 2, file, UPPER_RIGHT, aux, &tileMap,RoomID);
		objectArray->emplace_back(wall);
	}
	if ((aux.x > begin.x) && (aux.y == begin.y)){
		Point p(tileMap.GetTileCenter(aux));
		string file = "img/parede_dir_tamanho_do_tile.png";
		Wall *wall = new Wall(p.x - tileMap.GetTileWidth() / 2, p.y + tileMap.GetTileHeight() / 2, file, UPPER_RIGHT, aux, &tileMap,RoomID);
		objectArray->emplace_back(wall);
	}
	door.x = x;
	door.y = y;
	cout << "door: " << door.x << "," << door.y << endl;
}


void Room::DeleteTileWall(Point p, int RoomID, vector<unique_ptr<GameObject>> *objectArray) {
	
	for (int j = 0; j < objectArray->size(); j++){
		if (objectArray->at(j)->Is("Wall")){
			if (objectArray->at(j)->roomID == RoomID) {
				if (objectArray->at(j)->tile.DisPoints(objectArray->at(j)->tile, p) == 0) {
					objectArray->erase(objectArray->begin() + j);
					j--;
				}
			}
		}
	}
}

void Room::InsertTileWall(Point p, int RoomID, vector<unique_ptr<GameObject>> *objectArray){
	Point aux = p;
	if ((aux.y < end.y) && (aux.x == end.x)){
		Point p(tileMap.GetTileCenter(aux));
		string file = "img/parede_esq_tamanho_do_tile.png";
		Wall *wall = new Wall(p.x - tileMap.GetTileWidth() / 2, p.y + tileMap.GetTileHeight() / 2, file, UPPER_LEFT, aux, &tileMap,RoomID);
		objectArray->emplace_back(wall);
	}
	if ((aux.y > begin.y) && (aux.x == begin.x)){
		Point p(tileMap.GetTileCenter(aux));
		string file = "img/parede_esq_tamanho_do_tile.png";
		Wall *wall = new Wall(p.x - tileMap.GetTileWidth() / 2, p.y + tileMap.GetTileHeight() / 2, file, UPPER_LEFT, aux, &tileMap,RoomID);
		objectArray->emplace_back(wall);
	}
	if ((aux.x < end.x) && (aux.y == end.y)){
		Point p(tileMap.GetTileCenter(aux));
		string file = "img/parede_dir_tamanho_do_tile.png";
		Wall *wall = new Wall(p.x - tileMap.GetTileWidth() / 2, p.y + tileMap.GetTileHeight() / 2, file, UPPER_RIGHT, aux,&tileMap ,RoomID);
		objectArray->emplace_back(wall);
	}
	if ((aux.x > begin.x) && (aux.y == begin.y)){
		Point p(tileMap.GetTileCenter(aux));
		string file = "img/parede_dir_tamanho_do_tile.png";
		Wall *wall = new Wall(p.x - tileMap.GetTileWidth() / 2, p.y + tileMap.GetTileHeight() / 2, file, UPPER_RIGHT, aux,&tileMap,RoomID);
		objectArray->emplace_back(wall);
	}
}

bool Room::IsInside(float x, float y){
	if (begin.x <= x <= end.x && begin.y <= y <= end.y){
		return true;
	}
	return false;

}

bool Room::IsInside(Point tile){
	if (begin.x <= tile.x && tile.x <= end.x && (begin.y <= tile.y) && tile.y <= end.y){
		return true;
	}
	return false;
}

int Room::GetID(){
	return RoomID;
}

Point Room::GetDoor(){
	return door;
}

RoomType Room::GetState(){
	return roomType;
}

void Room::SetBegin(Point begin){
	this->begin = begin;
}

void Room::SetEnd(Point end){
	this->end = end;
}

Point Room::GetTileCenterRoom(){
	Point p;
	p.x = (begin.x + (int)((end.x - begin.x)/2));
	p.y = (begin.y + (int)((end.y - begin.y)/2));
	return p;
}

Point Room::GetBegin() {
	return begin;
}

Point Room::GetEnd() {
	return end;
}