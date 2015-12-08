#ifndef MAPGIMMICK_H
#define MAPGIMMICK_H

#include "Map.h"
class Library;

class MapGimmick
{
private:
	Library*		m_pLibrary;
	CustomVertex	m_MapGimmick_Tex[MAP_HEIGHT][MAP_WIDTH][4];
	Position		m_MapGimmick_Pos[MAP_HEIGHT][MAP_WIDTH];
	int				m_GimmickData[MAP_HEIGHT][MAP_WIDTH];


public:
	MapGimmick(Library* pLibrary);
	~MapGimmick();
	void Control();
	void Draw(float DrawPosX, float DrawPosY );
	bool CsvRead(const char* filename);
	void MapTex_UV_Set();
	void MapTex_XY_Set(float Posx, float Posy);
	int GimmickCheck(float x, float y);

};

#endif