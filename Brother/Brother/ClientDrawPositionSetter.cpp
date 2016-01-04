#include "ClientDrawPositionSetter.h"
#include "ClientMap.h"


ClientDrawPositionSetter::ClientDrawPositionSetter(ClientMap* pMap) :m_pMap(pMap)
{

}

ClientDrawPositionSetter::~ClientDrawPositionSetter()
{

}

void ClientDrawPositionSetter::DrawPositionXSet(float x)
{
	m_pMap->m_DrawPositionX = x;
}

void ClientDrawPositionSetter::DrawPositionYSet(float y)
{
	m_pMap->m_DrawPositionY = y;
}