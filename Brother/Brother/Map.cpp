#include "Map.h"
#include "Library.h"
#include "GameScene.h"
#include "MapGimmick.h"
#include "MapBackGround.h"
#include "MapObject.h"
#include <stdio.h>

Map::Map(Library* pLibrary) : m_pLibrary(pLibrary)
{
	m_pMapObject = new MapObject(m_pLibrary);

	m_pMapGimmick = new MapGimmick(m_pLibrary);

	m_pMapBackGround = new MapBackGround(m_pLibrary);
}

Map::~Map()
{
	delete m_pMapObject;
	delete m_pMapGimmick;
	delete m_pMapBackGround;
}


void Map::Control()
{
	m_pMapBackGround->Control();
	m_pMapGimmick->Control();
	m_pMapObject->Control();
}

void Map::Draw()
{
	m_pMapBackGround->MapTex_UV_Set(m_DrawPositionX, m_DrawPositionY);
	m_pMapGimmick->MapTex_UV_Set(m_DrawPositionX, m_DrawPositionY);
	m_pMapObject->MapTex_UV_Set(m_DrawPositionX, m_DrawPositionY);


	m_pMapBackGround->MapTex_XY_Set(m_DrawPositionX, m_DrawPositionY);
	m_pMapGimmick->MapTex_XY_Set(m_DrawPositionX, m_DrawPositionY);
	m_pMapObject->MapTex_XY_Set(m_DrawPositionX, m_DrawPositionY);


	m_pMapBackGround->Draw(m_DrawPositionX, m_DrawPositionY);
	m_pMapGimmick->Draw(m_DrawPositionX, m_DrawPositionY);
	m_pMapObject->Draw(m_DrawPositionX, m_DrawPositionY);
}


int Map::GimmickCheck(float x, float y)
{
	return m_pMapGimmick->GimmickCheck(x, y);
}

int Map::ObjectCheck(float x, float y)
{
	return m_pMapObject->ObjectCheck(x, y);
}

int Map::BackGroundCheck(float x, float y)
{
	return m_pMapBackGround->BackGroundCheck(x, y);
}
