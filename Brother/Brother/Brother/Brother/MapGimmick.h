#ifndef MAPGIMMICK_H
#define MAPGIMMICK_H

#include "Map.h"
class Library;

class MapGimmick
{
private:
	Library*		m_pLibrary;
	int				m_GimmickData[MAP_HEIGHT][MAP_WIDTH];


public:
	MapGimmick(Library* pLibrary);
	~MapGimmick();
	void Control();
	void Draw();
	bool CsvRead(const char* filename);
	void MapTex_XY_Set();
	int GimmickCheck(float x, float y);

};

#endif