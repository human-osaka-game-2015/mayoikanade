#ifndef MAPGIMMICK_H
#define MAPGIMMICK_H

#define SWITCH_COUNT_INIT 0
#define MAP_GIMMICK_NONE 0

#include <vector>
#include "Map.h"

class Library;
class Switch;
class Gate;


class MapGimmick
{
private:
	Library*					m_pLibrary;
	CustomVertex				m_MapGimmick_Tex[MAP_HEIGHT][MAP_WIDTH][SQUARE_VERTEX];
	Position					m_MapGimmick_Pos[MAP_HEIGHT][MAP_WIDTH];

public:
	MapGimmick(Library* pLibrary);
	~MapGimmick();
	void Draw(float DrawPosX, float DrawPosY );
	bool CsvRead(const char* filename);
	void MapTex_UV_Set(float Posx, float Posy);
	void MapTex_XY_Set(float Posx, float Posy);
	int GimmickCheck(float x, float y); 
	void SwitchOn(float x,float y);
	void SwitchOnYoung(float x, float y);
	void SwitchOff(float x, float y);
	bool HoleCheck(float x, float y);
	bool WoodBoxHoleCheck(float x, float y);
	bool GrassPortRaitCheck(float x,float y);
	bool GrassCheck(float x, float y);
	bool AppleCheck(float x, float y);
	bool ClearCheck(float x, float y);
	void MapStartPos(float* x, float* y);
	int	m_GimmickData[MAP_HEIGHT][MAP_WIDTH];

};

#endif