#include "ServerMap.h"
#include "Library.h"
#include "ServerGameScene.h"
#include "ServerMapGimmick.h"
#include "ServerMapBackGround.h"
#include "ServerMapObject.h"
#include <stdio.h>

ServerMap::ServerMap(Library* pLibrary) : m_pLibrary(pLibrary)
{
	m_pMapObject = new ServerMapObject(m_pLibrary);

	m_pMapGimmick = new ServerMapGimmick(m_pLibrary);

	m_pMapBackGround = new ServerMapBackGround(m_pLibrary);
}

ServerMap::~ServerMap()
{
	delete m_pMapObject;
	delete m_pMapGimmick;
	delete m_pMapBackGround;
}


void ServerMap::Control()
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

void ServerMap::Draw()
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


int ServerMap::GimmickCheck(float x, float y)
{
	return m_pMapGimmick->GimmickCheck(x, y);
}

void ServerMap::SwitchOn(float x, float y)
{
	return m_pMapGimmick->SwitchOn(x, y);
}

void ServerMap::SwitchOnYoung(float x, float y)
{
	return m_pMapGimmick->SwitchOnYoung(x, y);
}

void ServerMap::SwitchOff(float x, float y)
{
	return m_pMapGimmick->SwitchOff(x, y);
}




int ServerMap::ObjectCheck(float x, float y)
{
	return m_pMapObject->ObjectCheck(x, y);
}

bool ServerMap::WoodBoxCheck(float x, float y)
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

bool ServerMap::WoodBoxSet(float x, float y)
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


int ServerMap::BackGroundCheck(float x, float y)
{
	return m_pMapBackGround->BackGroundCheck(x, y);
}
