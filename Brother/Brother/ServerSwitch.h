#ifndef SWITCH_H
#define SWITCH_H

#include "ServerMap.h"

class Library;


class ServerSwitch
{
private:
	Library*	m_pLibrary;
	int*		m_pMap[MAP_WIDTH];
	int			m_Type;
	int			m_SwitchId;

public:
	ServerSwitch(Library* pLibrary, int id, int MapGimmickData[MAP_HEIGHT][MAP_WIDTH], int SwitchType);
	~ServerSwitch();
	inline int GetSwitchId(){ return m_SwitchId; };
	

};


#endif