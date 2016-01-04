#include "Vertex.h"
#include "Library.h"
#include "ServerGameScene.h"
#include "ServerSwitch.h"


ServerSwitch::ServerSwitch(Library* pLibrary, int id, int MapGimmickData[MAP_HEIGHT][MAP_WIDTH], int SwitchType) :
	m_SwitchId(id), 
	m_Type(SwitchType), 
	m_pLibrary(pLibrary)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		m_pMap[i] = MapGimmickData[i];
	}
}

ServerSwitch::~ServerSwitch()
{

}

