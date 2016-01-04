#include "ClientMapBackGround.h"
#include "ClientGameScene.h"
#include "Library.h"


ClientMapBackGround::ClientMapBackGround(Library* pLibrary) :m_pLibrary(pLibrary)
{
	CsvRead("alpha_back .csv");
}

ClientMapBackGround::~ClientMapBackGround()
{

}

bool ClientMapBackGround::CsvRead(const char* filename)
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


void ClientMapBackGround::MapTex_UV_Set(float Posx, float Posy)
{
	int count_x = int((Posx - 64) / MAPTIP_SIZE);
	int count_y = int((Posy - 64) / MAPTIP_SIZE);


	if (count_x < 0)
	{
		count_x = 0;
	}
	if (count_y < 0)
	{
		count_y = 0;
	}


	//描画領域を求めて代入 余分に一つ先も読んでるので64足している
	int ScreenRight = int((Posx + SCREEN_SIZEX + 64) / MAPTIP_SIZE);
	int ScreenBottom = int((Posy + SCREEN_SIZEY + 64) / MAPTIP_SIZE);

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
			switch (m_BackGroundData[i][j])
			{
			case GRASS_01:
				m_pLibrary->MakeVertex(GRASS_01, m_MapBackGround_Tex[i][j]);
				break;

			case GROUND_01:
				m_pLibrary->MakeVertex(GROUND_01, m_MapBackGround_Tex[i][j]);

				break;
			default:
				for (int x = 0; x < VERTEXNUM; x++)
				{
					m_MapBackGround_Tex[i][j][x].color = DEFAULTCOLOR;
					m_MapBackGround_Tex[i][j][x].rhw = DEFAULTRHW;
					m_MapBackGround_Tex[i][j][x].z = DEFAULTZ;
					m_MapBackGround_Tex[i][j][x].tu = 0;
					m_MapBackGround_Tex[i][j][x].tv = 0;
				}
				break;
			}
		}
	}
}

void ClientMapBackGround::MapTex_XY_Set(float Posx, float Posy)
{
	int count_x = int((Posx - 64) / MAPTIP_SIZE);
	int count_y = int((Posy - 64) / MAPTIP_SIZE);


	if (count_x < 1)
	{
		count_x = 1;
	}
	if (count_y < 1)
	{
		count_y = 1;
	}


	//描画領域を求めて代入 余分に一つ先も読んでるので64足している
	int ScreenRight = int((Posx + SCREEN_SIZEX + 64) / MAPTIP_SIZE);
	int ScreenBottom = int((Posy + SCREEN_SIZEY + 64) / MAPTIP_SIZE);

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
			//背景のXYを入れる
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


void ClientMapBackGround::Control()
{

}

void ClientMapBackGround::Draw(float DrawPosX, float DrawPosY)
{
	int count_x = int((DrawPosX - 64) / MAPTIP_SIZE);
	int count_y = int((DrawPosY - 64) / MAPTIP_SIZE);


	if (count_x < 0)
	{
		count_x = 0;
	}
	if (count_y < 0)
	{
		count_y = 0;
	}


	//描画領域を求めて代入 余分に一つ先も読んでるので64足している
	int ScreenRight = int((DrawPosX + SCREEN_SIZEX + 64) / MAPTIP_SIZE);
	int ScreenBottom = int((DrawPosY + SCREEN_SIZEY + 64) / MAPTIP_SIZE);

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

int ClientMapBackGround::BackGroundCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);

	return m_BackGroundData[arrayy][arrayx];
}
