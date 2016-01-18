#ifndef MAPGIMMICK_H
#define MAPGIMMICK_H

#include <vector>
#include "Map.h"

class Library;
class Switch;
class Gate;


class MapGimmick
{
private:
	Library*					m_pLibrary;
	CustomVertex				m_MapGimmick_Tex[MAP_HEIGHT][MAP_WIDTH][4];
	Position					m_MapGimmick_Pos[MAP_HEIGHT][MAP_WIDTH];
	std::vector<Switch>			m_Switch;
	std::vector<Gate>			m_Gate;

public:
	MapGimmick(Library* pLibrary);
	~MapGimmick();
	void Control();
	void Draw(float DrawPosX, float DrawPosY );
	void Init();
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

	int	m_GimmickData[MAP_HEIGHT][MAP_WIDTH];

};

#endif