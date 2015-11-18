#include "Map.h"
#include "Library.h"
#include "GameScene.h"
#include <stdio.h>

Map::Map(Library* pLibrary, LPDIRECT3DTEXTURE9 pTexture) :m_pLibrary(pLibrary), m_pTexture(pTexture)
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		m_pMapObject[i] = new MapObject(m_pLibrary);
	}

	for (int i = 0; i < GIMMICK_MAX; i++)
	{
		m_pMapGimmick[i] = new MapGimmick(m_pLibrary);
	}

	for (int i = 0; i < BACKGROUND_MAX; i++)
	{
		m_pMapBackGround[i] = new MapBackGround(m_pLibrary);
	}


}

Map::~Map()
{
	for (int i = 0; i < BACKGROUND_MAX; i++)
	{
		delete m_pMapBackGround[i];
	}

	for (int i = 0; i < GIMMICK_MAX; i++)
	{
		delete m_pMapGimmick[i];
	}

	for (int i = 0; i < OBJECT_MAX; i++)
	{
		delete m_pMapObject[i];

	}
}

bool Map::CsvRead(const char* filename, MAP_ID MapId)
{
	FILE*  fp = NULL;
	fopen_s(&fp, filename, "r");
	
	if (fp == NULL)
	{
		return false;
	}
	
	switch (MapId)
	{
	case MAP_OBJECT:

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				fscanf_s(fp, "%d,", &m_ObjectData[i][j], _countof(m_ObjectData));
			}
		}
		break;
	case MAP_GIMMICK:
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				fscanf_s(fp, "%d,", &m_GimmickData[i][j], _countof(m_GimmickData));
			}
		}
		break;
	case MAP_BACKGROUND:
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				fscanf_s(fp, "%d,", &m_BackGroundData[i][j], _countof(m_BackGroundData));
			}
		}
		break;
	}
	fclose(fp);

	return true;
}

void Map::MapTex_UV_Set(MAP_ID MapId)
{
	switch (MapId)
	{
	case MAP_OBJECT:
		CsvRead("alpha_obj.csv", MAP_OBJECT);
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				switch (m_ObjectData[i][j])
				{
				case WOOD_01:
					m_pLibrary->MakeVertex(WOOD_01 , m_MapObject_Tex[i][j]);
					break;

				case WOOD_02:
					m_pLibrary->MakeVertex(WOOD_02 , m_MapObject_Tex[i][j]);
					break;

				case WOOD_03:
					m_pLibrary->MakeVertex(WOOD_03 , m_MapObject_Tex[i][j]);
					break;

				case WOOD_04:
					m_pLibrary->MakeVertex(WOOD_04 , m_MapObject_Tex[i][j]);
					break;

				}
			}
		}
		break;

	case MAP_BACKGROUND:
		CsvRead("alpha_back .csv", MAP_BACKGROUND);
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				switch (m_BackGroundData[i][j])
				{
				case GRASS_01:
					m_pLibrary->MakeVertex(GRASS_01 , m_MapBackGround_Tex[i][j]);
					break;

				case GROUND_01:
					m_pLibrary->MakeVertex(GROUND_01, m_MapBackGround_Tex[i][j]);

					break;
				}
			}
		}
		break;

	case MAP_GIMMICK:
		//αでは無し
		break;
	}
}

void Map::MapTex_XY_Set()
{
	//この変数を基にマップチップのCustomVertexを生成するので1から始めている
	int count_y = 1;
	int count_x = 1;

	for (count_y = 1; count_y <= MAP_HEIGHT; count_y++)
	{
		for (count_x = 1; count_x <= MAP_WIDTH; count_x++)
		{
			//背景のXYを入れる
			m_MapBackGround_Pos[count_y - 1][count_x - 1].x = (float)(MAPTIP_SIZE * count_x) - MAPTIP_DEFAULT_POSX;
			m_MapBackGround_Pos[count_y - 1][count_x - 1].y = (float)(MAPTIP_SIZE * count_y) - MAPTIP_DEFAULT_POSY;
			m_MapBackGround_Pos[count_y - 1][count_x - 1].w = (float)MAPTIP_SIZE;
			m_MapBackGround_Pos[count_y - 1][count_x - 1].h = (float)MAPTIP_SIZE;
			m_pLibrary->xySet(m_MapBackGround_Pos[count_y - 1][count_x - 1], m_MapBackGround_Tex[count_y - 1][count_x - 1]);

			//当たり判定用のXYを入れる
			m_MapObject_Pos[count_y - 1][count_x - 1].x = (float)(MAPTIP_SIZE * count_x) - MAPTIP_DEFAULT_POSX;
			m_MapObject_Pos[count_y - 1][count_x - 1].y = (float)(MAPTIP_SIZE * count_y) - MAPTIP_DEFAULT_POSY;
			m_MapObject_Pos[count_y - 1][count_x - 1].w = (float)MAPTIP_SIZE;
			m_MapObject_Pos[count_y - 1][count_x - 1].h = (float)MAPTIP_SIZE;
			m_pLibrary->xySet(m_MapObject_Pos[count_y - 1][count_x - 1], m_MapObject_Tex[count_y - 1][count_x - 1]);
		}
	}
}

int Map::ObjectCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0 ;

	arrayx = int(x / 64);
	arrayy = int(y / 64);

	
	return m_ObjectData[arrayy][arrayx];
}

int Map::GimmickCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);

	
	return m_GimmickData[arrayy][arrayx];
}

int Map::BackGroundCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);

	return m_BackGroundData[arrayy][arrayx];
}

void Map::Control()
{
	MapTex_XY_Set();

	MapTex_UV_Set(MAP_BACKGROUND);
	MapTex_UV_Set(MAP_OBJECT);
}

void Map::Draw()
{
	
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			m_pLibrary->Set_Draw_Tex(m_pTexture, m_MapBackGround_Tex[i][j]);
			m_pLibrary->Set_Draw_Tex(m_pTexture, m_MapObject_Tex[i][j]);
		}
	}
}

bool Map::StageInit(const char* Objname, const char* Gimmickname, const char* Backname)
{
	if (CsvRead(Objname, MAP_OBJECT) == false)
	{
		MessageBox(0, "ステージのオブジェクト構成に失敗しました", "", MB_OK);
		return false;
	}

	if (CsvRead(Gimmickname, MAP_GIMMICK) == false)
	{
		MessageBox(0, "ステージのギミック構成に失敗しました", "", MB_OK);
		return false;
	}

	if (CsvRead(Backname, MAP_BACKGROUND) == false)
	{
		MessageBox(0, "ステージの背景構成に失敗しました", "", MB_OK);
		return false;
	}


	return true;
}