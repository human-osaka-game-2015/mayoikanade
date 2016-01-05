#ifndef MAPBACKGROUND_H
#define MAPBACKGROUND_H

#include "ServerMap.h"
class Library;



class ServerMapBackGround
{
private:
	Library*		m_pLibrary;
	CustomVertex	m_MapBackGround_Tex[MAP_HEIGHT][MAP_WIDTH][4];
	Position		m_MapBackGround_Pos[MAP_HEIGHT][MAP_WIDTH];


public:
	ServerMapBackGround(Library* pLibrary);
	~ServerMapBackGround();
	void Control();
	void Draw(float DrawPosX, float DrawPosY);
	bool CsvRead(const char* filename);
	void MapTex_UV_Set(float Posx, float Posy);
	void MapTex_XY_Set(float Posx, float Posy);
	int BackGroundCheck(float x, float y);

	int				m_BackGroundData[MAP_HEIGHT][MAP_WIDTH];


};


#endif