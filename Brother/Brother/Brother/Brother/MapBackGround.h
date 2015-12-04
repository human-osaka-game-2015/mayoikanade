#ifndef MAPBACKGROUND_H
#define MAPBACKGROUND_H

#include "Map.h"
class Library;



class MapBackGround
{
private:
	Library*		m_pLibrary;
	CustomVertex	m_MapBackGround_Tex[MAP_HEIGHT][MAP_WIDTH][4];
	int				m_BackGroundData[MAP_HEIGHT][MAP_WIDTH];
	Position		m_MapBackGround_Pos[MAP_HEIGHT][MAP_WIDTH];


public:
	MapBackGround(Library* pLibrary);
	~MapBackGround();
	void Draw();
	bool CsvRead(const char* filename);
	void MapTex_UV_Set();
	void MapTex_XY_Set();
	int BackGroundCheck(float x, float y);

};


#endif