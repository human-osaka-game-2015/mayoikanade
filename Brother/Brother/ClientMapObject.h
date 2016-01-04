#ifndef cMAPOBJECT_H
#define cMAPOBJECT_H

#include "ClientMap.h"
class Library;



class ClientMapObject
{
private:
	Library*		m_pLibrary;
	CustomVertex	m_MapObject_Tex[MAP_HEIGHT][MAP_WIDTH][4];
	Position		m_MapObject_Pos[MAP_HEIGHT][MAP_WIDTH];


public:
	ClientMapObject(Library* pLibrary);
	~ClientMapObject();
	void Control();
	void Draw(float DrawPosX, float DrawPosY);
	bool CsvRead(const char* filename);
	void MapTex_UV_Set(float Posx, float Posy);
	void MapTex_XY_Set(float Posx, float Posy);
	int ObjectCheck(float x, float y);

	bool WoodBoxCheck(float x, float y);
	bool WoodBoxSet(float x, float y);


	int				m_ObjectData[MAP_HEIGHT][MAP_WIDTH];

};

#endif