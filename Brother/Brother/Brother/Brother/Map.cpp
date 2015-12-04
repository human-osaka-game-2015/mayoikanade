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

}

void Map::Draw()
{
	m_pMapBackGround->MapTex_UV_Set();
	m_pMapObject->MapTex_UV_Set();

	m_pMapBackGround->MapTex_XY_Set();
	m_pMapObject->MapTex_XY_Set();

	m_pMapBackGround->Draw();
	m_pMapObject->Draw();
}

//bool Map::StageInit(const char* Objname, const char* Gimmickname, const char* Backname)
//{
//	if (CsvRead(Objname, MAP_OBJECT) == false)
//	{
//		MessageBox(0, "ステージのオブジェクト構成に失敗しました", "", MB_OK);
//		return false;
//	}
//
//	if (CsvRead(Gimmickname, MAP_GIMMICK) == false)
//	{
//		MessageBox(0, "ステージのギミック構成に失敗しました", "", MB_OK);
//		return false;
//	}
//
//	if (CsvRead(Backname, MAP_BACKGROUND) == false)
//	{
//		MessageBox(0, "ステージの背景構成に失敗しました", "", MB_OK);
//		return false;
//	}
//
//
//	return true;
//}


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
