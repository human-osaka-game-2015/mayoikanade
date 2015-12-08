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

void MapBackGround::MapTex_XY_Set(float Posx,float Posy)
{
	int count_x = (Posx - 64) / MAPTIP_SIZE;
	int count_y = (Posy - 64) / MAPTIP_SIZE;


	if (count_x < 1)
	{
		count_x = 1;
	}
	if (count_y < 1)
	{
		count_y = 1;
	}


	//�`��̈�����߂đ�� �]���Ɉ����ǂ�ł�̂�64�����Ă���
	int ScreenRight = (Posx + SCREEN_SIZEX + 64) / MAPTIP_SIZE;
	int ScreenBottom = (Posy + SCREEN_SIZEY + 64) / MAPTIP_SIZE;

	if (ScreenRight > MAP_WIDTH)
	{
		ScreenRight = MAP_WIDTH;
	}
	if (ScreenBottom > MAP_HEIGHT)
	{
		ScreenBottom = MAP_HEIGHT;
	}


	for (int i = count_y; i <= ScreenBottom; i++)
	{
		for (int j = count_x; j <= ScreenRight; j++)
		{
			//�w�i��XY������
			m_MapBackGround_Pos[i - 1][j - 1].x = (float)(MAPTIP_SIZE * j) - MAPTIP_DEFAULT_POSX;
			m_MapBackGround_Pos[i - 1][j - 1].y = (float)(MAPTIP_SIZE * i) - MAPTIP_DEFAULT_POSY;
			m_MapBackGround_Pos[i - 1][j - 1].w = (float)MAPTIP_SIZE;
			m_MapBackGround_Pos[i - 1][j - 1].h = (float)MAPTIP_SIZE;
			m_MapBackGround_Pos[i - 1][j - 1].x -= Posx;
			m_MapBackGround_Pos[i - 1][j - 1].y -= Posy;


			m_pLibrary->xySet(m_MapBackGround_Pos[i - 1][j - 1], m_MapBackGround_Tex[i - 1][j - 1]);

			
		}
	}
}


void MapBackGround::Control()
{

}

void MapBackGround::Draw(float DrawPosX, float DrawPosY)
{
	int count_x = (DrawPosX - 64) / MAPTIP_SIZE;
	int count_y = (DrawPosY - 64) / MAPTIP_SIZE;


	if (count_x < 0)
	{
		count_x = 0;
	}
	if (count_y < 0)
	{
		count_y = 0;
	}


	//�`��̈�����߂đ�� �]���Ɉ����ǂ�ł�̂�64�����Ă���
	int ScreenRight = (DrawPosX + SCREEN_SIZEX + 64) / MAPTIP_SIZE;
	int ScreenBottom = (DrawPosY + SCREEN_SIZEY + 64) / MAPTIP_SIZE;

	if (ScreenRight > MAP_WIDTH)
	{
		ScreenRight = MAP_WIDTH;
	}
	if (ScreenBottom > MAP_HEIGHT)
	{
		ScreenBottom = MAP_HEIGHT;
	}

	for (int i = count_y; i < ScreenBottom; i++)
	{
		for (int j = count_x; j < ScreenRight; j++)
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
