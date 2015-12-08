#include "DrawPositionSetter.h"
#include "Map.h"


DrawPositionSetter::DrawPositionSetter(Map* pMap) :m_pMap(pMap)
{

}

DrawPositionSetter::~DrawPositionSetter()
{

}

void DrawPositionSetter::DrawPositionXSet(float x)
{
	m_pMap->m_DrawPositionX = x;
}

void DrawPositionSetter::DrawPositionYSet(float y)
{
	m_pMap->m_DrawPositionY= y;
}