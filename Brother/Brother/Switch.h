#ifndef SWITCH_H
#define SWITCH_H

#include "Map.h"

class Library;


class Switch
{
private:
	Library*	m_pLibrary;
	int*		m_pMap[MAP_WIDTH];
	int			m_Type;
	int			m_SwitchId;

public:
	Switch(Library* pLibrary, int id, int MapGimmickData[MAP_HEIGHT][MAP_WIDTH], int SwitchType);
	~Switch();
	inline int GetSwitchId(){ return m_SwitchId; };
	

};


#endif