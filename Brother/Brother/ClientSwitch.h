#ifndef cSWITCH_H
#define cSWITCH_H

#include "ClientMap.h"

class Library;


class ClientSwitch
{
private:
	Library*	m_pLibrary;
	int*		m_pMap[MAP_WIDTH];
	int			m_Type;
	int			m_SwitchId;

public:
	ClientSwitch(Library* pLibrary, int id, int MapGimmickData[MAP_HEIGHT][MAP_WIDTH], int SwitchType);
	~ClientSwitch();
	inline int GetSwitchId(){ return m_SwitchId; };


};


#endif