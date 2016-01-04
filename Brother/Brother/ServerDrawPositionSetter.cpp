#include "ServerDrawPositionSetter.h"
#include "ServerMap.h"


ServerDrawPositionSetter::ServerDrawPositionSetter(ServerMap* pMap) :m_pMap(pMap)
{

}

ServerDrawPositionSetter::~ServerDrawPositionSetter()
{

}

void ServerDrawPositionSetter::DrawPositionXSet(float x)
{
	m_pMap->m_DrawPositionX = x;
}

void ServerDrawPositionSetter::DrawPositionYSet(float y)
{
	m_pMap->m_DrawPositionY= y;
}