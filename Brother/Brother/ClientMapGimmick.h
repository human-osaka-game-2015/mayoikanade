#ifndef sMAPGIMMICK_H
#define sMAPGIMMICK_H

#include <vector>
#include "ClientMap.h"

class Library;
class ClientSwitch;
class ClientGate;


class ClientMapGimmick
{
private:
	Library*				m_pLibrary;
	CustomVertex			m_MapGimmick_Tex[MAP_HEIGHT][MAP_WIDTH][4];
	Position				m_MapGimmick_Pos[MAP_HEIGHT][MAP_WIDTH];
	std::vector<ClientSwitch>		m_Switch;
	std::vector<ClientGate>		m_Gate;

public:
	ClientMapGimmick(Library* pLibrary);
	~ClientMapGimmick();
	void Control();
	void Draw(float DrawPosX, float DrawPosY);
	void Init();
	bool CsvRead(const char* filename);
	void MapTex_UV_Set(float Posx, float Posy);
	void MapTex_XY_Set(float Posx, float Posy);
	int GimmickCheck(float x, float y);
	void SwitchOn(float x, float y);
	void SwitchOnYoung(float x, float y);
	void SwitchOff(float x, float y);
	bool HoleCheck(float x, float y);
	bool WoodBoxHoleCheck(float x, float y);
	int						m_GimmickData[MAP_HEIGHT][MAP_WIDTH];

};

#endif