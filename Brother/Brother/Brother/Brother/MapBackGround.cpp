#include "MapBackGround.h"
#include "GameScene.h"
#include "Library.h"


MapBackGround::MapBackGround(Library* pLibrary) :m_pLibrary(pLibrary)
{
	CsvRead("alpha_back .csv");
}

MapBackGround::~MapBackGround()
{

}

bool MapBackGround::CsvRead(const char* filename)
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
			fscanf_s(fp, "%d,", &m_BackGroundData[i][j], _countof(m_BackGroundData));
		}
	}
	fclose(fp);

	return true;
}


void MapBackGround::MapTex_UV_Set()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (m_BackGroundData[i][j])
			{
			case GRASS_01:
				m_pLibrary->MakeVertex(GRASS_01, m_MapBackGround_Tex[i][j]);
				break;

			case GROUND_01:
				m_pLibrary->MakeVertex(GROUND_01, m_MapBackGround_Tex[i][j]);

				break;
			}
		}
	}
}

void MapBackGround::MapTex_XY_Set()
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

			
		}
	}
}

void MapBackGround::Draw()
{


	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			m_pLibrary->DrawTexture(TEX_GAME, m_MapBackGround_Tex[i][j]);
		}
	}
}

int MapBackGround::BackGroundCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);

	return m_BackGroundData[arrayy][arrayx];
}
