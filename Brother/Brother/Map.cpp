#include "Map.h"
#include "Library.h"
#include "ServerGameScene.h"
#include "MapGimmick.h"
#include "MapBackGround.h"
#include "MapObject.h"
#include <stdio.h>

Map::Map(Library* pLibrary) : 
m_pLibrary(pLibrary)
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
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if ((m_pMapGimmick->m_GimmickData[i][j]/10000) == SWITCH_BLUE_02)
			{
				if (m_pMapObject->m_ObjectData[i][j] == WOODBOX)
				{
					SwitchOn(j * 64.f, i * 64.f);
				}
				else
				{
					SwitchOff(j * 64.f, i * 64.f);
				}
			}
		}
	}

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

void Map::SwitchOn(float x, float y)
{
	return m_pMapGimmick->SwitchOn(x, y);
}

void Map::SwitchOnYoung(float x, float y)
{
	return m_pMapGimmick->SwitchOnYoung(x, y);
}

void Map::SwitchOff(float x, float y)
{
	return m_pMapGimmick->SwitchOff(x, y);
}




int Map::ObjectCheck(float x, float y)
{
	return m_pMapObject->ObjectCheck(x, y);
}

bool Map::WoodBoxCheck(float x, float y)
{
	if (m_pMapObject->WoodBoxCheck(x, y) == true)
	{
		return true;
	}
	else if (m_pMapGimmick->WoodBoxHoleCheck(x, y) == true)
	{
		return true;
	}

	return false;
}

bool Map::WoodBoxSet(float x, float y)
{
	switch (m_pMapGimmick->GimmickCheck(x, y))
	{
	case GATEPOST_01:
		return false;
		break;
	case GATEPOST_02:
		return false;
		break;
	case GATE_01:
		return false;
		break;
	case GATE_02:
		return false;
		break;
	case GATEPOST_PORTRAIT_01:
		return false;
		break;
	case GATEPOST_PORTRAIT_02:
		return false;
		break;
	case GATE_PORTRAIT_01:
		return false;
		break;
	case GATE_PORTRAIT_02:
		return false;
		break;
	
	}

	bool isBoxSet;

	if (m_pMapObject->WoodBoxSet(x, y))
	{
		isBoxSet = true;
	}
	if (m_pMapGimmick->HoleCheck(x, y))
	{
		m_pMapObject->WoodBoxCheck(x,y);
		isBoxSet = true;
	}

	if (isBoxSet)
	{
		m_pMapGimmick->SwitchOn(x, y);
	}

	return isBoxSet;
}


int Map::BackGroundCheck(float x, float y)
{
	return m_pMapBackGround->BackGroundCheck(x, y);
}


bool Map::GrassPortRaitCheck(float x, float y)
{
	return m_pMapGimmick->GrassPortRaitCheck(x, y);
}


bool Map::GrassCheck(float x, float y)
{
	return m_pMapGimmick->GrassCheck(x, y);
}

bool Map::AppleCheck(float x, float y)
{
	return m_pMapGimmick->AppleCheck(x, y);
}

void Map::MapChange()
{
	switch (m_mapstage)
	{
	case STAGE1:
		m_pMapBackGround->CsvRead("Stage1_Background.csv");
		m_pMapObject->CsvRead("Stage1_Object.csv");
		m_pMapGimmick->CsvRead("Stage1_Gimmick.csv");
		break;
	case STAGE2:
		m_pMapBackGround->CsvRead("Stage1_Background.csv");
		m_pMapObject->CsvRead("Stage1_Object.csv");
		m_pMapGimmick->CsvRead("Stage1_Gimmick.csv");
		break;
	case STAGE3:
		m_pMapBackGround->CsvRead("Stage1_Background.csv");
		m_pMapObject->CsvRead("Stage1_Object.csv");
		m_pMapGimmick->CsvRead("Stage1_Gimmick.csv");
		break;
	case STAGE4:
		m_pMapBackGround->CsvRead("Stage1_Background.csv");
		m_pMapObject->CsvRead("Stage1_Object.csv");
		m_pMapGimmick->CsvRead("Stage1_Gimmick.csv");
		break;
	}
}

bool Map::ClearCheck(float x,float y)
{
	return m_pMapGimmick->ClearCheck(x,y);
}
