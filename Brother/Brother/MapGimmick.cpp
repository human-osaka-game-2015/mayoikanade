#include"MapGimmick.h"
#include "Library.h"

MapGimmick::MapGimmick(Library* pLibrary) :m_pLibrary(pLibrary)
{

}

MapGimmick::~MapGimmick()
{

}

bool MapGimmick::CsvRead(const char* filename)
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
			fscanf_s(fp, "%d,", &m_GimmickData[i][j], _countof(m_GimmickData));
		}
	}
	fclose(fp);

	return true;
}

void MapGimmick::Control()
{

}

void MapGimmick::Draw(float DrawPosX, float DrawPosY)
{

}

int MapGimmick::GimmickCheck(float x, float y)
{
	int arrayx = 0, arrayy = 0;
	arrayx = int(x / 64);
	arrayy = int(y / 64);

	return m_GimmickData[arrayy][arrayx];
}




void MapGimmick::MapTex_UV_Set()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			/*switch (m_GimmickData[i][j])
			{
			default:

				break;
			}*/
		}
	}
}


void MapGimmick::MapTex_XY_Set(float Posx, float Posy)
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


	//•`‰æ—Ìˆæ‚ð‹‚ß‚Ä‘ã“ü —]•ª‚Éˆê‚Âæ‚à“Ç‚ñ‚Å‚é‚Ì‚Å64‘«‚µ‚Ä‚¢‚é
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
			{
				//“–‚½‚è”»’è—p‚ÌXY‚ð“ü‚ê‚é
				m_MapGimmick_Pos[i - 1][j - 1].x = (float)(MAPTIP_SIZE * j) - MAPTIP_DEFAULT_POSX;
				m_MapGimmick_Pos[i - 1][j - 1].y = (float)(MAPTIP_SIZE * i) - MAPTIP_DEFAULT_POSY;
				m_MapGimmick_Pos[i - 1][j - 1].w = (float)MAPTIP_SIZE;
				m_MapGimmick_Pos[i - 1][j - 1].h = (float)MAPTIP_SIZE;
				m_MapGimmick_Pos[i - 1][j - 1].x -= Posx;
				m_MapGimmick_Pos[i - 1][j - 1].y -= Posy;

				m_pLibrary->xySet(m_MapGimmick_Pos[i - 1][j - 1], m_MapGimmick_Tex[i - 1][j - 1]);
			}
		}
	}
}