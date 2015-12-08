#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include "Map.h"
class Library;



class MapObject
{
private:
	Library*		m_pLibrary;
	CustomVertex	m_MapObject_Tex[MAP_HEIGHT][MAP_WIDTH][4];
	Position		m_MapObject_Pos[MAP_HEIGHT][MAP_WIDTH];
	int				m_ObjectData[MAP_HEIGHT][MAP_WIDTH];


public:
	MapObject(Library* pLibrary);
	~MapObject();
	void Control();
	void Draw(float DrawPosX, float DrawPosY);
	bool CsvRead(const char* filename);
	void MapTex_UV_Set();
	void MapTex_XY_Set(float Posx, float Posy);
	int ObjectCheck(float x, float y);


};

#endif