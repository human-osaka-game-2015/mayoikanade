#include"MapObject.h"
#include "GameScene.h"
#include "Library.h"


MapObject::MapObject(Library* pLibrary) :m_pLibrary(pLibrary)
{
	CsvRead("alpha_obj.csv");
}

MapObject::~MapObject()
{

}

bool MapObject::CsvRead(const char* filename)
{
	FILE*  fp = NULL;
	fopen_s(&fp, filename, "r");

	if (fp == NULL)
	{
		return false;
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			fscanf_s(fp, "%d,", &m_ObjectData[i][j], _countof(m_ObjectData));
		}
	}
	fclose(fp);

	return true;
}

void MapObject::MapTex_UV_Set()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (m_ObjectData[i][j])
			{
			case WOOD_01:
				m_pLibrary->MakeVertex(WOOD_01, m_MapObject_Tex[i][j]);
				break;

			case WOOD_02:
				m_pLibrary->MakeVertex(WOOD_02, m_MapObject_Tex[i][j]);
				break;

			case WOOD_03:
				m_pLibrary->MakeVertex(WOOD_03, m_MapObject_Tex[i][j]);
				break;

			case WOOD_04:
				m_pLibrary->MakeVertex(WOOD_04, m_MapObject_Tex[i][j]);
				break;

			}
		}
	}
}


int MapObject::ObjectCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;

	arrayx = int(x / 64);
	arrayy = int(y / 64);


	return m_ObjectData[arrayy][arrayx];
}

void MapObject::MapTex_XY_Set()
{
	//この変数を基にマップチップのCustomVertexを生成するので1から始めている
	int count_y = 1;
	int count_x = 1;

	for (count_y = 1; count_y <= MAP_HEIGHT; count_y++)
	{
		for (count_x = 1; count_x <= MAP_WIDTH; count_x++)
		{
			//当たり判定用のXYを入れる
			m_MapObject_Pos[count_y - 1][count_x - 1].x = (float)(MAPTIP_SIZE * count_x) - MAPTIP_DEFAULT_POSX;
			m_MapObject_Pos[count_y - 1][count_x - 1].y = (float)(MAPTIP_SIZE * count_y) - MAPTIP_DEFAULT_POSY;
			m_MapObject_Pos[count_y - 1][count_x - 1].w = (float)MAPTIP_SIZE;
			m_MapObject_Pos[count_y - 1][count_x - 1].h = (float)MAPTIP_SIZE;
			m_pLibrary->xySet(m_MapObject_Pos[count_y - 1][count_x - 1], m_MapObject_Tex[count_y - 1][count_x - 1]);
		}
	}
}

void MapObject::Control()
{

}

void MapObject::Draw()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			m_pLibrary->DrawTexture(TEX_GAME, m_MapObject_Tex[i][j]);
		}
	}
}
