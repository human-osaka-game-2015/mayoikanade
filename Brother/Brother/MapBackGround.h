#ifndef MAPBACKGROUND_H
#define MAPBACKGROUND_H

#include "Map.h"
class Library;



class MapBackGround
{
private:
	Library*		m_pLibrary;
	CustomVertex	m_MapBackGround_Tex[MAP_HEIGHT][MAP_WIDTH][4];
	Position		m_MapBackGround_Pos[MAP_HEIGHT][MAP_WIDTH];


public:
	MapBackGround(Library* pLibrary);
	~MapBackGround();
	void Control();
	void Draw(float DrawPosX, float DrawPosY);
	bool CsvRead(const char* filename);
	void MapTex_UV_Set(float Posx, float Posy);
	void MapTex_XY_Set(float Posx, float Posy);
	int BackGroundCheck(float x, float y);

	int				m_BackGroundData[MAP_HEIGHT][MAP_WIDTH];


};


#endif