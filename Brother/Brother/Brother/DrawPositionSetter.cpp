#include "DrawPositionSetter.h"
#include "Map.h"


DrawPositionSetter::DrawPositionSetter()
{

}

DrawPositionSetter::~DrawPositionSetter()
{

}

void DrawPositionSetter::DrawPositionXSet(int x)
{
	m_pMap->m_DrawPositionX = x;
}

void DrawPositionSetter::DrawPositionYSet(int y)
{
	m_pMap->m_DrawPositionY= y;
}